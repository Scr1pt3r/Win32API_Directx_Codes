#include <windows.h>
#include <windowsx.h>

// A assinatura da função WindowProc
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Ponto inicial de todo programa Windows
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// Handle da Janela, que vai ser preenchida	
	HWND hWnd;

	// Estrutura que mantém a definição da classe
	WNDCLASSEX wc;

	// Esta estrutura armazena eventos e mensagens
	MSG msg;

	// Limpa a classe da janela
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// Preenche a estrutura com a informção necessária
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
		L"Hello World in Win32", // Título da janela
		WS_OVERLAPPEDWINDOW,     // Estilo da janela
		300,                     // Posição X
		300,                     // Posição Y
		500,                     // Largura da janela
		400,                     // Altura da janela
		NULL,					 // Não tem janela-pai, NULL
		NULL,					 // Não tem menus, NULL
		hInstance,				 // Handle da aplicação
		NULL);					 // Usado com múltiplas janelas, NULL

	// Exibe a janela na tela
	ShowWindow(hWnd, nCmdShow);

	// Entra no loop principal
	// Espera pela próxima mensagem na fila e armezena o resultado em 'msg'
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// Traduz as mensagens para o formato correto
		TranslateMessage(&msg);

		// Envia a mensagem para a função WindowProc
		DispatchMessage(&msg);
	}

	// Saindo do loop retorna este parâmetro da mensagem WM_QUIT para o Windows
	return msg.wParam;
}

// Este é o manipulador de mensagens principal do programa
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Executa um código para cada mensagem
	switch (message)
	{
		// Está mensagem é enviada quando a janela é destruida 
		//(ex: quando o usuário clica no botão fechar)
		case WM_DESTROY:
		{
			// Fecha a aplicação
			PostQuitMessage(0);
			return 0;
		}
		break;
	}

	// Manipula as outras mensagens que não 'tratamos'
	return DefWindowProc(hWnd, message, wParam, lParam);
}