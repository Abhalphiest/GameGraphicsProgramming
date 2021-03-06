#include "../headers/Game.h"
#include "../headers/Vertex.h"
#include "DDSTextureLoader.h"
// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore( 
		hInstance,		    // The application's handle
		"Engenuity GGP",    // Text for the window's title bar
		1280,			    // Width of the window's client area
		720,			    // Height of the window's client area
		true)			    // Show extra stats (fps) in title bar?
{


#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.");
#endif
}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	delete scenemanager;    // Handles its own memory
    delete spriteBatch;
    delete spriteFont;
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
    gs = BEGIN;     // Remember to press SPACE to change state to playing. Commented out b/c it's annoying while testing

	scenemanager = SceneManager::getInstance();
	scenemanager->SetContext(context);
	scenemanager->SetDevice(device);
	scenemanager->SetSamplerState();
	scenemanager->BuildSkybox();
    scene1 = scenemanager->LoadScene("scenes/entrywayAlt.txt");
	scene2 = scenemanager->LoadScene("scenes/parlorAlt.txt");
    //scene3 = scenemanager->LoadScene("scenes/walltestscene.txt");
    scene3 = 1;     // Think I've reached a new low of lazy here. . .
	scenemanager->SetScene(scene1);

    spriteBatch = new DirectX::SpriteBatch(context);
    spriteFont = new DirectX::SpriteFont(device, L"Assets/Fonts/candara.spritefont");
	
	


	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
}

// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	FirstPersonController* fpc = scenemanager->GetFPC();
	
	std::vector<Collider> sceneColliders = scenemanager->GetCurrentScene()->GetColliders();
	//handle camera movement here until I can move this logic to an input manager
	if (GetAsyncKeyState('W') & 0x8000) { fpc->Move(sceneColliders, XMFLOAT3(0, 0, MOVE_SCALE*deltaTime)); }
	if (GetAsyncKeyState('S') & 0x8000) { fpc->Move(sceneColliders, XMFLOAT3(0, 0, -deltaTime*MOVE_SCALE)); }
	if (GetAsyncKeyState('A') & 0x8000) { fpc->Move(sceneColliders, XMFLOAT3(-deltaTime*MOVE_SCALE, 0, 0)); }
	if (GetAsyncKeyState('D') & 0x8000) { fpc->Move(sceneColliders, XMFLOAT3(deltaTime*MOVE_SCALE, 0, 0)); }
    if (GetAsyncKeyState('F') & 0x8000 == 0x8000) { fpc->ToggleLightState(); }
    if (GetAsyncKeyState('E') & 0x8000 == 0x8000) {
        int colIndex = scenemanager->GetCurrentScene()->CollidingWithDoor(1.5f);
        if (colIndex != -1)
        {
            Door exitDoor = scenemanager->GetCurrentScene()->GetDoor(colIndex);
            uint entryDoor = exitDoor.destIndex;
            int destSceneIndex = scenemanager->GetSceneByName(exitDoor.destScene);
            if (destSceneIndex != -1)
            {
                DirectX::XMFLOAT3 fpcEntryPos = scenemanager->SetScene(destSceneIndex, entryDoor);
                DirectX::XMFLOAT3 fpcColliderSize = { 1.0f, 1.0f, 1.0f };
                DirectX::XMVECTOR fpcEntryPosVec = DirectX::XMLoadFloat3(&fpcEntryPos);
                // Vector from door to origin
                DirectX::XMVECTOR displaceVector = DirectX::XMVectorSubtract({ 0.0f, 0.0f, 0.0f }, fpcEntryPosVec);
                DirectX::XMVECTOR colliderSizeVec = DirectX::XMLoadFloat3(&fpcColliderSize);

                // Project colliderSizeVec onto vector to origin
                displaceVector = DirectX::XMVector3Normalize(displaceVector);
                float collSizeScale;
                DirectX::XMStoreFloat(&collSizeScale, DirectX::XMVector3Dot(colliderSizeVec, displaceVector));
                displaceVector = DirectX::XMVectorScale(displaceVector, collSizeScale);

                // Always assumed that moving towards center will displace FPC correctly
                fpcEntryPosVec = DirectX::XMVectorAdd(fpcEntryPosVec, displaceVector);
                DirectX::XMStoreFloat3(&fpcEntryPos, fpcEntryPosVec);
                fpcEntryPos.y = 1.5f;   // Make sure we don't start in floor
                fpc->camera->SetPosition(fpcEntryPos);
            }
        }
    }
	
	if (GetAsyncKeyState('1') & 0x8000) { scenemanager->SetScene(scene1); }
	if (GetAsyncKeyState('2') & 0x8000) { scenemanager->SetScene(scene2); }
    if (GetAsyncKeyState('3') & 0x8000) { scenemanager->SetScene(scene3); }
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) { gs = PLAYING; }
	
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = {0.4f, 0.6f, 0.75f, 0.0f};
    // TODO: Added for demo, consider removing
    const float blackBG[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
    //context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearRenderTargetView(backBufferRTV, blackBG);
    if (gs == BEGIN)
    {
        
        spriteBatch->Begin();
        spriteFont->DrawString(spriteBatch, L"Press [SPACE] to enter the survival horror. . .", XMFLOAT2(470, 360));
        spriteBatch->End();
		context->OMSetDepthStencilState(NULL,0);
    }
	

	context->ClearDepthStencilView(
		depthStencilView, 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);
	
    if (gs == PLAYING) {
        scenemanager->RenderCurrentScene();

		
    }



	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);
}


#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
    // TODO: Add check to rot val either here or in the camera to prevent over-rotation
    if (buttonState & 0x0001) //left button down
    {
        XMFLOAT3 rotVec = XMFLOAT3(CAMERA_DELTA*(y - prevMousePos.y), CAMERA_DELTA*(x - prevMousePos.x), 0);
        scenemanager->GetFPC()->SetOrientation(rotVec);
    }
	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;
}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
}
#pragma endregion