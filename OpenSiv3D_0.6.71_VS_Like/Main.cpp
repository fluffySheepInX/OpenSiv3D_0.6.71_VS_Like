# include <Siv3D.hpp> // OpenSiv3D v0.6.7

// ウィンドウの幅
const double WindowSizeWidth = 1200;
// ウィンドウの高さ
const double WindowSizeHeight = 800;
// マップの幅
int mapWidth = -1;
// マップの高さ
int mapHeight = -1;
// プレイヤーのサイズ(幅)
const int PlayerWidth = 50;
// プレイヤーのサイズ(高さ)
const int PlayerHeight = 50;
const String PathImage = U"image001";
const String PathMusic = U"music001";
const String PathSound = U"sound001";

enum Language {
	English,
	Japan,
	C
};
enum GameMode {
	Game,
	Menu,
	Lan,
	Option,
	Exit
};

class WindowManager {

public:
	Language language = Language::English;

public:
	GameMode ShowSelectLangWindow()
	{
		// ウィンドウのタイトル | Window title
		Window::SetTitle(U"MagicAr-Ver0.1");
		// ウィンドウのサイズ | Window size
		Window::Resize(WindowSizeWidth, WindowSizeHeight);
		//// フルスクリーンモードのデフォルトを有効にするか | Whether to enable fullscreen mode by default
		//Window::SetFullscreen(true);
		// 背景の色を設定する | Set the background color
		Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
		// フレームレートの上限を設定する | Set the frame rate limit

		// ウィンドウを中心に移動
		Window::Centering();
		//ウィンドウを手動でリサイズできるようにする
		Window::SetStyle(WindowStyle::Sizable);
		//仮想ウィンドウサイズが新しいシーンのサイズになります
		Scene::SetResizeMode(ResizeMode::Virtual);

		// 画像を使用する為のTexture宣言
		String lan = PathImage + U"/btnLanguage.png";
		const Texture textureSiv3DKun{ lan, TextureDesc::Unmipped };
		const int width = 270;
		const int height = 100;
		const int centerHeight = (WindowSizeHeight / 2) - (height / 2);
		const int centerWidth = (WindowSizeWidth / 2) - (width / 2);
		//第1引数x座標,第2引数y座標,第3引数幅,第4引数高さ
		const Rect rectSiv3DKun{ centerWidth , centerHeight - 300,width,height };
		// フォントを作成
		const Font font{ 40 };
		// font を使って text を pos の位置に描画したときのテキストの領域を取得
		String text = U"English";
		String text2 = U"日本語";
		RectF rectText = font(text).region();
		RectF rectText2 = font(text2).region();
		RectF rect = { (WindowSizeWidth / 2) - (rectText.w / 2), 300,rectText.w,60 };
		RectF rect2 = { (WindowSizeWidth / 2) - (rectText2.w / 2), 370,rectText2.w,60 };

		while (System::Update())
		{
			//draw群
			{
				rectSiv3DKun(textureSiv3DKun).draw();
				rect.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				rect2.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(U"English").draw((WindowSizeWidth / 2) - (rectText.w / 2), 300, ColorF{ 0.25 });
				font(U"日本語").draw((WindowSizeWidth / 2) - (rectText2.w / 2), 370, ColorF{ 0.25 });
			}

			//押されたら次の画面へ進む
			if (rect.leftClicked())
			{
				language = English;
				break;
			}
			if (rect2.leftClicked())
			{
				language = Japan;
				break;
			}
		}
		return Menu;
	}
	GameMode ShowMenu()
	{
		const Font font{ 40 };
		String text = U"";
		String textSelectLang = U"";
		String textOption = U"";
		String textExit = U"";
		switch (language)
		{
		case English:
			text += U"Go hunt";
			textSelectLang += U"SelectLang";
			textOption += U"Option";
			textExit += U"Game end";
			break;
		case Japan:
			text += U"狩りへ行く";
			textSelectLang += U"言語選択";
			textOption += U"設定";
			textExit += U"ゲーム終了";
			break;
		case C:
			break;
		default:
			break;
		}
		int height = 100;
		int height2 = 200;
		int height3 = 300;
		int height4 = 400;
		RectF rectText = font(text).region();
		RectF rect = { (WindowSizeWidth / 2) - (rectText.w / 2), height,rectText.w,60 };
		RectF rectText2 = font(textSelectLang).region();
		RectF rect2 = { (WindowSizeWidth / 2) - (rectText2.w / 2), height2,rectText2.w,60 };
		RectF rectText3 = font(textOption).region();
		RectF rect3 = { (WindowSizeWidth / 2) - (rectText3.w / 2), height3,rectText3.w,60 };
		RectF rectText4 = font(textExit).region();
		RectF rect4 = { (WindowSizeWidth / 2) - (rectText4.w / 2), height4,rectText4.w,60 };

		GameMode ga = Game;
		while (System::Update())
		{
			//draw
			{
				rect.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(text).draw((WindowSizeWidth / 2) - (rectText.w / 2), height, ColorF{ 0.25 });
				rect2.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(textSelectLang).draw((WindowSizeWidth / 2) - (rectText2.w / 2), height2, ColorF{ 0.25 });
				rect3.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(textOption).draw((WindowSizeWidth / 2) - (rectText3.w / 2), height3, ColorF{ 0.25 });
				rect4.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(textExit).draw((WindowSizeWidth / 2) - (rectText4.w / 2), height4, ColorF{ 0.25 });
			}

			//押されたら画面遷移
			if (rect.leftClicked())
			{
				ga = Game;
				break;
			}
			if (rect2.leftClicked())
			{
				ga = Lan;
				break;
			}
			if (rect3.leftClicked())
			{
				ga = Option;
				break;
			}
			if (rect4.leftClicked())
			{
				ga = Exit;
				break;
			}
		}

		return ga;
	}
	GameMode ShowOption()
	{
		const Font font{ 40 };

		String text = U"";
		String textBackMenu = U"";

		switch (language)
		{
		case English:
			text += U"BGM volume";
			textBackMenu += U"Back to menu";
			break;
		case Japan:
			text += U"BGM音量";
			textBackMenu += U"メニューへ戻る";
			break;
		case C:
			break;
		default:
			break;
		}

		int height = 100;
		int height2 = 200;
		RectF rectText = font(text).region();
		RectF rect = { (WindowSizeWidth / 2) - (rectText.w / 2), height,rectText.w,60 };
		RectF rectText2 = font(textBackMenu).region();
		RectF rect2 = { (WindowSizeWidth / 2) - (rectText2.w / 2), height2,rectText2.w,60 };

		GameMode ga = Game;
		while (System::Update())
		{
			//draw
			{
				rect.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(text).draw((WindowSizeWidth / 2) - (rectText.w / 2), height, ColorF{ 0.25 });
				rect2.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(textBackMenu).draw((WindowSizeWidth / 2) - (rectText2.w / 2), height2, ColorF{ 0.25 });
			}

			if (rect.leftClicked())
			{

			}
			if (rect2.leftClicked())
			{
				ga = Menu;
				break;
			}

		}
		return ga;
	}
	GameMode PlayGame()
	{
		const Font font{ FontMethod::MSDF, 48, Typeface::Bold };
		// 絵文字からテクスチャを作成する | Create a texture from an emoji
		const Texture texturePlayer{ U"🦖"_emoji };
		//texturePlayer.resized(PlayerWidth);
		// マップ画像を使用する為のTexture宣言
		const Texture textureMap{ PathImage + U"/map.png", TextureDesc::Mipped };
		mapWidth = textureMap.width();
		mapHeight = textureMap.height();
		//textureMap.resized(mapWidth);
		// プレイヤーの移動スピード | Player's movement speed
		double speed = 600.0;
		// プレイヤーが右を向いているか | Whether player is facing right
		bool isPlayerFacingRight = true;
		// プレイヤーの位置
		Vec2 playerPos(WindowSizeWidth / 2, WindowSizeHeight / 2);

		while (System::Update())
		{
			const ScopedRenderStates2D sampler{ SamplerState::RepeatLinear };

			//draw
			{
				// マップを描く | Draw the map
				DrawMap(playerPos, textureMap, font);

				// プレイヤーを描く | Draw the player
				DrawPlayer(texturePlayer, isPlayerFacingRight);
			}

			{
				// Aキーが押されていたら | If A key is pressed
				if (KeyA.pressed())
				{
					// プレイヤーが左に移動する | Player moves left
					playerPos.x = (playerPos.x + speed * Scene::DeltaTime());
					isPlayerFacingRight = false;
				}

				// Sキーが押されていたら | If S key is pressed
				if (KeyS.pressed())
				{
					// プレイヤーが下に移動する | Player moves bottom
					playerPos.y = (playerPos.y - speed * Scene::DeltaTime());
				}

				// Dキーが押されていたら | If D key is pressed
				if (KeyD.pressed())
				{
					// プレイヤーが右に移動する | Player moves right
					playerPos.x = (playerPos.x - speed * Scene::DeltaTime());
					isPlayerFacingRight = true;
				}

				// Wキーが押されていたら | If W key is pressed
				if (KeyW.pressed())
				{
					// プレイヤーが上に移動する | Player moves up
					playerPos.y = (playerPos.y + speed * Scene::DeltaTime());
				}
			}
		}
		return Menu;
	}
private:
	void ShowConfigWindowTest()
	{
		// ウィンドウのタイトル | Window title
		Window::SetTitle(U"TestGame-Ver0.1");
		// ウィンドウのサイズ | Window size
		Window::Resize(1200, 800);
		//// フルスクリーンモードのデフォルトを有効にするか | Whether to enable fullscreen mode by default
		//Window::SetFullscreen(true);
		// 背景の色を設定する | Set the background color
		Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
		// フレームレートの上限を設定する | Set the frame rate limit

		// ウィンドウを中心に移動
		Window::Centering();
		//ウィンドウを手動でリサイズできるようにする
		Window::SetStyle(WindowStyle::Sizable);
		//仮想ウィンドウサイズが新しいシーンのサイズになります
		Scene::SetResizeMode(ResizeMode::Virtual);

		// 画像を使用する為のTexture宣言
		const Texture textureSiv3DKun{ U"example/siv3d-kun.png", TextureDesc::Mipped };

		// 
		const int pointOneX = 500;
		const int pointOneY = 60;
		const Polygon hexagonOne = Shape2D::Hexagon(60, Vec2{ pointOneX, pointOneY });
		const Vec2 offsetOne = Vec2(pointOneX, pointOneY);

		while (System::Update())
		{
			{
				// Polygon に対し、(35, 180) を画像の中心とするようにテクスチャを貼り付けて描画
				hexagonOne.draw(HSV{ 240, 0.5, 1.0 });
				hexagonOne.toBuffer2D(Arg::center = (Vec2{ 35, 180 } + offsetOne), textureSiv3DKun.size())
					.draw(textureSiv3DKun);
			}

			//hexagonが押されたら次の画面へ進む
			if (hexagonOne.leftClicked())
			{
				break;
			}
		}
	}
	GameMode PlayGameTest()
	{
		const Font font{ FontMethod::MSDF, 48, Typeface::Bold };
		// 絵文字からテクスチャを作成する | Create a texture from an emoji
		const Texture texturePlayer{ U"🦖"_emoji };
		//texturePlayer.resized(PlayerWidth);
		// マップ画像を使用する為のTexture宣言
		const Texture textureMap{ PathImage + U"/map.png", TextureDesc::Mipped };
		mapWidth = textureMap.width();
		mapHeight = textureMap.height();
		//textureMap.resized(mapWidth);
		// プレイヤーの移動スピード | Player's movement speed
		double speed = 600.0;
		// プレイヤーが右を向いているか | Whether player is facing right
		bool isPlayerFacingRight = true;
		// プレイヤーの位置
		Vec2 playerPos(WindowSizeWidth / 2, WindowSizeHeight / 2);

		while (System::Update())
		{
			//draw
			{
				// マップを描く | Draw the map
				DrawMap(playerPos, textureMap, font);

				// プレイヤーを描く | Draw the player
				DrawPlayer(texturePlayer, isPlayerFacingRight);
			}

			{
				// Aキーが押されていたら | If A key is pressed
				if (KeyA.pressed())
				{
					// プレイヤーが左に移動する | Player moves left
					playerPos.x = Max((playerPos.x - speed * Scene::DeltaTime()), WindowSizeWidth / 2 - (mapWidth / 2));
					isPlayerFacingRight = false;
				}

				// Sキーが押されていたら | If S key is pressed
				if (KeyS.pressed())
				{
					// プレイヤーが下に移動する | Player moves bottom
					playerPos.y = Min((playerPos.y + speed * Scene::DeltaTime()), (WindowSizeHeight / 2) + (mapHeight / 2));
					isPlayerFacingRight = true;
				}

				// Dキーが押されていたら | If D key is pressed
				if (KeyD.pressed())
				{
					// プレイヤーが右に移動する | Player moves right
					playerPos.x = Min((playerPos.x + speed * Scene::DeltaTime()), (WindowSizeWidth / 2) + (mapWidth / 2));
					isPlayerFacingRight = true;
				}

				// Wキーが押されていたら | If W key is pressed
				if (KeyW.pressed())
				{
					// プレイヤーが上に移動する | Player moves up
					playerPos.y = Max((playerPos.y - speed * Scene::DeltaTime()), (WindowSizeHeight / 2) - (mapHeight / 2));
					isPlayerFacingRight = true;
				}
			}
		}
		return Menu;
	}

	// マップを描画する
	void DrawMap(Vec2 playerPos, Texture mapTexture, Font font)
	{
		// 差分を計算する
		double x = playerPos.x - WindowSizeWidth / 2;
		double y = playerPos.y - WindowSizeHeight / 2;

		// マップの左上の位置を計算する
		Vec2 mapPos = Vec2(-x + (-(mapWidth / 2) + WindowSizeWidth / 2), -y + (-(mapHeight / 2) + WindowSizeHeight / 2));

		mapTexture(mapPos.x, mapPos.y, mapWidth, mapHeight).draw();
	}
	void DrawMapTest(Vec2 playerPos, Texture mapTexture, Font font)
	{
		// 差分を計算する
		double x = playerPos.x - WindowSizeWidth / 2;
		double y = playerPos.y - WindowSizeHeight / 2;

		// マップの左上の位置を計算する
		Vec2 mapPos = Vec2(-x + (-(mapWidth / 2) + WindowSizeWidth / 2), -y + (-(mapHeight / 2) + WindowSizeHeight / 2));

		// マップを描画する
		mapTexture.draw(mapPos);
	}
	// プレイヤーを描画する
	void DrawPlayer(Texture playerTexture, bool isPlayerFacingRight)
	{
		playerTexture
			.scaled(1)
			.mirrored(isPlayerFacingRight)
			.draw((WindowSizeWidth / 2) - PlayerWidth, (WindowSizeHeight / 2) - PlayerHeight);
	}
};


// メイン関数 | Main function
void Main()
{
	// 音声ファイルを読み込み
	String lan = PathMusic + U"/PreparationBattle001.wav";
	// Audio を作成
	const Audio audio{ lan };
	// 再生
	audio.play();

	// 画面管理クラスの宣言
	std::shared_ptr<WindowManager> windowManager = std::make_shared<WindowManager>();
	// 初期画面は言語選択画面
	GameMode ga = windowManager->ShowSelectLangWindow();
	// ループのフラグ
	bool checkLoop = true;
	// 初期画面の次はメニュー画面
	ga = windowManager->ShowMenu();

	while (checkLoop and System::Update())
	{
		switch (ga)
		{
		case Game:
			// ゲーム本編
			ga = windowManager->PlayGame();
			break;
		case Menu:
			// メニュー画面
			ga = windowManager->ShowMenu();
			break;
		case Lan:
			// 言語選択画面
			ga = windowManager->ShowSelectLangWindow();
			break;
		case Option:
			// オプション画面
			ga = windowManager->ShowOption();
			break;
		case Exit:
			// 終了
			checkLoop = false;
			// BGM終了
			audio.stop();
			break;
		default:
			break;
		}
	}

	// 画像ファイルからテクスチャを作成する | Create a texture from an image file
	const Texture texture{ U"example/windmill.png" };

	// 絵文字からテクスチャを作成する | Create a texture from an emoji
	const Texture emoji{ U"🦖"_emoji };

	// 太文字のフォントを作成する | Create a bold font with MSDF method
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	// テキストに含まれる絵文字のためのフォントを作成し、font に追加する | Create a font for emojis in text and add it to font as a fallback
	const Font emojiFont{ 48, Typeface::ColorEmoji };
	font.addFallback(emojiFont);

	// ボタンを押した回数 | Number of button presses
	int32 count = 0;

	// チェックボックスの状態 | Checkbox state
	bool checked = false;

	// プレイヤーの移動スピード | Player's movement speed
	double speed = 200.0;

	// プレイヤーの X 座標 | Player's X position
	double playerPosX = 400;

	// プレイヤーが右を向いているか | Whether player is facing right
	bool isPlayerFacingRight = true;

	//System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	while (System::Update())
	{
		// テクスチャを描く | Draw the texture
		texture.draw(20, 20);

		// テキストを描く | Draw text
		font(U"Hello, Siv3D!🎮").draw(64, Vec2{ 20, 340 }, ColorF{ 0.2, 0.4, 0.8 });

		// 指定した範囲内にテキストを描く | Draw text within a specified area
		font(U"Siv3D (シブスリーディー) は、ゲームやアプリを楽しく簡単な C++ コードで開発できるフレームワークです。")
			.draw(18, Rect{ 20, 430, 480, 200 }, Palette::Black);

		// 長方形を描く | Draw a rectangle
		Rect{ 540, 20, 80, 80 }.draw();

		// 角丸長方形を描く | Draw a rounded rectangle
		RoundRect{ 680, 20, 80, 200, 20 }.draw(ColorF{ 0.0, 0.4, 0.6 });

		// 円を描く | Draw a circle
		Circle{ 580, 180, 40 }.draw(Palette::Seagreen);

		// 矢印を描く | Draw an arrow
		Line{ 540, 330, 760, 260 }.drawArrow(8, SizeF{ 20, 20 }, ColorF{ 0.4 });

		// 半透明の円を描く | Draw a semi-transparent circle
		Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 1.0, 0.0, 0.0, 0.5 });

		// ボタン | Button
		if (SimpleGUI::Button(U"count: {}"_fmt(count), Vec2{ 520, 370 }, 120, (checked == false)))
		{
			// カウントを増やす | Increase the count
			++count;
		}

		// チェックボックス | Checkbox
		SimpleGUI::CheckBox(checked, U"Lock \U000F033E", Vec2{ 660, 370 }, 120);

		// スライダー | Slider
		SimpleGUI::Slider(U"speed: {:.1f}"_fmt(speed), speed, 100, 400, Vec2{ 520, 420 }, 140, 120);

		// 左キーが押されていたら | If left key is pressed
		if (KeyLeft.pressed())
		{
			// プレイヤーが左に移動する | Player moves left
			playerPosX = Max((playerPosX - speed * Scene::DeltaTime()), 60.0);
			isPlayerFacingRight = false;
		}

		// 右キーが押されていたら | If right key is pressed
		if (KeyRight.pressed())
		{
			// プレイヤーが右に移動する | Player moves right
			playerPosX = Min((playerPosX + speed * Scene::DeltaTime()), 740.0);
			isPlayerFacingRight = true;
		}

		// プレイヤーを描く | Draw the player
		emoji.scaled(0.75).mirrored(isPlayerFacingRight).drawAt(playerPosX, 540);
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
