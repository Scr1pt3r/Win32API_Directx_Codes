#include <windows.h>
#include <windowsx.h>

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

	// Preenche a estrutura com a inform��o necess�ria
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
		L"WindowClass1",         // Nome da classe da janela
		L"Hello World in Win32", // T�tulo da janela
		WS_OVERLAPPEDWINDOW,     // Estilo da janela
		300,                     // Posi��o X
		300,                     // Posi��o Y
		500,                     // Largura da janela
		400,                     // Altura da janela
		NULL,					 // N�o tem janela-pai, NULL
		NULL,					 // N�o tem menus, NULL
		hInstance,				 // Handle da aplica��o
		NULL);					 // Usado com m�ltiplas janelas, NULL

	// Exibe a janela na tela
	ShowWindow(hWnd, nCmdShow);

	// Entra no loop principal
	// Espera pela pr�xima mensagem na fila e armezena o resultado em 'msg'
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// Traduz as mensagens para o formato correto
		TranslateMessage(&msg);

		// Envia a mensagem para a fun��o WindowProc
		DispatchMessage(&msg);
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