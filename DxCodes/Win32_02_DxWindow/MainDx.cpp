/*
* Copyright � 2015, Fernando Vellozo <fernando.vellozo@live.com>
* Todos os diretos reservados.
*
* Aten��o: C�digo criado para fins de estudo podendo sofrer altera��es.
*/


#include <windows.h>
#include <windowsx.h>
#include <d3d10.h>
#include <d3dx10.h>

// Inclui as bibliotecas para o Direct3D
#pragma comment (lib, "d3d10.lib")
#pragma comment (lib, "d3dx10.lib")

// Declara��es Globais
ID3D10Device* device;        // Apontador para o device do Direct3D
ID3D10RenderTargetView* rtv; // Apontador para o render target
IDXGISwapChain* swapchain;   // Apontador para classe de controle do Backbuffer

							 // Assinatura das fun��es
void InitD3D(HWND hWnd);     // Configura e inicializa o Direct3D
void Clean3D3(void);         // Fecha o Direct3D e libera a mem�ria usada
void Render(void);           // Desenha o frame do jogo

// A assinatura da fun��o WindowProc
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Ponto inicial de todo programa Windows
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// Handle da Janela, que vai ser preenchida	
	HWND hWnd;

	// Estrutura que mant�m a defini��o da classe
	WNDCLASSEX wc;

	// Esta estrutura armazena eventos e mensagens
	MSG msg;

	// Limpa a classe da janela
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// Preenche a estrutura com a informa��o necess�ria
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	// Registra a classe da janela
	RegisterClassEx(&wc);

	// Cria a janela e obtem seu handle
	hWnd = CreateWindowEx(NULL,
		L"WindowClass1",            // Nome da classe da janela
		L"Hello World in Direct3D", // T�tulo da janela
		WS_OVERLAPPEDWINDOW,        // Estilo da janela
		450,                        // Posi��o X
		300,                        // Posi��o Y
		800,                        // Largura da janela
		600,                        // Altura da janela
		NULL,                       // N�o tem janela-pai, NULL
		NULL,                       // N�o tem menus, NULL
		hInstance,                  // Handle da aplica��o
		NULL);                      // Usado com m�ltiplas janelas, NULL

	// Exibe a janela na tela
	ShowWindow(hWnd, nCmdShow);

	// Configura e Inicializa o Direct3D
	InitD3D(hWnd); // Recebe o handle da janela criada

	// Entra no loop principal
	// Espera pela pr�xima mensagem na fila e armezena o resultado em 'msg'
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// Traduz as mensagens para o formato correto
		TranslateMessage(&msg);

		// Envia a mensagem para a fun��o WindowProc
		DispatchMessage(&msg);

		// Verifica se � hora de fechar
		if (msg.message == WM_QUIT)
			break;

		// C�digo do jogo vai aqui
		//...
		//...
		Render();
	}

	// Saindo do loop retorna este par�metro da mensagem WM_QUIT para o Windows
	return msg.wParam;
}

// Este � o manipulador de mensagens principal do programa
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Executa um c�digo para cada mensagem
	switch (message)
	{
		// Est� mensagem � enviada quando a janela � destruida 
		//(ex: quando o usu�rio clica no bot�o fechar)
		case WM_DESTROY:
		{
			// Fecha a aplica��o
			PostQuitMessage(0);
			return 0;
		}
		break;
	}

	// Manipula as outras mensagens que n�o 'tratamos'
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// Esta fun��o inicializa o D3D e deixa pronto para uso
void InitD3D(HWND hWnd)
{
	// Cria a estrutura para conter varios descritores do swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// Limpa a estrutura para o uso
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1; // Cria 2 buffer, um para frente, outro escondido
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Use cores de 32-bits
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Diz como o chain deve ser usado
	scd.OutputWindow = hWnd; // Seta a janela(handle) que ser� usada com o Direct3D
	scd.SampleDesc.Count = 1; // Seta o n�vel do multi-sampling
	scd.SampleDesc.Quality = 0; // Seta a quantidade de multi-sampling
	scd.Windowed = TRUE; // Seta em modo janela ou fullscreen

	// Cria a classe do device e a classe do swapchain usando as informa��es contidas na estrutura 'scd'
	D3D10CreateDeviceAndSwapChain(NULL,
		D3D10_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		D3D10_SDK_VERSION,
		&scd,
		&swapchain,
		&device);

	// Pega o endere�o do back buffer e usa ele para criar o render target
	ID3D10Texture2D* pBackBuffer;	
	swapchain->GetBuffer(0, __uuidof(ID3D10Texture2D), // __uuidof = Recupera o GUID vinculado � express�o
						(LPVOID*)&pBackBuffer);
	device->CreateRenderTargetView(pBackBuffer, NULL, &rtv);
	pBackBuffer->Release();

	// Seta o render target como o back buffer
	device->OMSetRenderTargets(1, &rtv, NULL);

	D3D10_VIEWPORT viewport; // Cria a estrutura do viewport

	// Limpa a estrutura para o uso
	ZeroMemory(&viewport, sizeof(D3D10_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 600;

	// Seta o viewport
	device->RSSetViewports(1, &viewport);
}

// Seta fun��o limpa tudo e libera da m�moria
void CleanD3D(void)
{
	swapchain->SetFullscreenState(FALSE, NULL); // Volta para o modo em janela
	swapchain->Release(); // Fecha e libera o swap chain
	rtv->Release(); // Fecha e libera o render target view
	device->Release(); // Fecha e libera o dispositivo 3D
}

// Esta fun��o desenha um �nico frame
void Render(void)
{
	// Pinta um azul
	device->ClearRenderTargetView(rtv, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f)); // RGBA

	// Joga o frame na tela
	swapchain->Present(0, 0);
}