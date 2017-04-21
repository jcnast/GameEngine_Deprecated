
/*
LRESULT InitGlut::WindowProcedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (window != ActiveWindow)
	{
	return;
	}

	switch (message)
	{
	case WM_SETFOCUS:
	{
		SetFocused(true);
		break;
	}
	case WM_KILLFOCUS:
	{
		SetFocused(false);
		break;
	}
	case WM_ACTIVATE:
		{
		if (LOWORD(wParam) == WA_ACTIVE)
			SetActive(true);
		else
			SetActive(false);
		break;
		}
	}
}

void InitGlut::SetFocused(bool focused)
{
	// clamp mouse inside window
	if (focused)
	{
		RECT rect;
		GetWindowRect(ActiveWindow, &rect);

		ClipCursor(&rect);
	}
}

void InitGlut::SetActive(bool active)
{
	SetFocused(active);
}
*/