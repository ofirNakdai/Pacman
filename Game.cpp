#include "Game.h"

Game::Game(int gameMode)
	:board(), pacman(), mode(gameMode)
{
	statusMap["Lives"] = 3;
	statusMap["Score"] = 0;
	statusMap["Difficulty"] = 0;
	statusMap["Screen"] = 0;
	this->load_screen_files();
}
Game::~Game()
{
	if (fruit != nullptr)
	{
		delete fruit;
	}
}
void Game::startGame()
{
	int count = 1, gameStatus = IN_PROGRESS;
	int* ghostDirection = new int[ghostArr.size()];
	char input = 's', temp = NULL;
	clearScreen();
	board.printBoard();
	printData();

	while (!_kbhit() || gameStatus == IN_PROGRESS)
	{
		if (_kbhit())
		{
			temp = _getch();
			if (temp == 27)
			{
				pauseGame();
			}
			else if (isValidMovementKey(temp))
			{
				input = temp;
			}
		}

		int fruit_save_mode_direction = 0;// 0 means no fruit
		gameStatus = makeTurn(input , ghostDirection, count, fruit_save_mode_direction);
		
	
		count++;
		if (gameStatus != IN_PROGRESS)
		{
			break;
		}
	}
	if (gameStatus == GAME_WON)
	{
		delete[] ghostDirection;
		clearScreen();
		cout << "Game Won" << endl;
		if (this->mode == SAVE_MODE)
					write_event_to_ResFile(this->getScore(), "Finished screen");

		system("pause");
		if (load_next_screen())
		{
			startGame();
		}
		else
		{
			clearScreen();
			menu();
		}
		
	}
	else if (gameStatus == GAME_OVER)
	{
		delete[] ghostDirection;
		clearScreen();
		cout << "Game Lost" << endl;

		if (this->mode == SAVE_MODE)
			write_event_to_ResFile(this->getScore(), "Finished screen");

		system("pause");
		setScore(0);
		setLives(3);
		board.setCrumbs(0);
		menu();
	}
}
bool Game::load_next_screen()
{
	if ((int)this->getScreenNum() + 1 >= (int)m_screenFiles.size())
	{// no more screens left

		system("cls");
		cout << "Game Finished!" << endl;
		system("pause");
		return false;
	}
	else
	{
		this->setScreenNum(this->getScreenNum() + 1);
		this->setCrumbs(0);
		this->clearGhostArr();
		this->LoadFile(this->get_curr_screen_file());
		system("cls");
		this->printBoard();
		this->printData();
	}
	return true;
}
int Game::makeTurn(char direction, int* ghostDirection, int turn, int& fruit_direcion)
{
	bool saveMode = (this->mode == SAVE_MODE);
	if (saveMode)
		write_pacman_to_file(direction);// pacman die

	int newX, newY;
	int moveResult, option;
	if (checkWall(direction, pacman.getX(), pacman.getY()) == false && (direction != 's' && direction != 'S'))
	{ //pacman
		newX = pacman.getX();
		newY = pacman.getY();
		getNewCoord(direction, &newX, &newY);
		moveResult = pacman.makeMovePacman(newX, newY, board);
		

		if (moveResult == 2)
		{//eat fruit
			setScore(getScore() + fruit->getValue());
			delete fruit;
			fruit = nullptr;
			board.getCellPtr(newX, newY)->setObject(&pacman);
			board.getCellPtr(newX, newY)->printCell();
			printData();
		}
		else if (moveResult == 1)
		{//eat crumb
			setScore(getScore() + 1);
			board.getCellPtr(newX, newY)->setObject(&pacman);
			board.getCellPtr(newX, newY)->printCell();
			printData();
			if (board.getCrumbs() == 0)
			{
				if (fruit != nullptr)
				{
					board.getCellPtr(fruit->getX(), fruit->getY())->printContent();
					delete fruit;
					fruit = nullptr;
				}
				return 1;
			}
		}
		else if (moveResult == 0)
		{
			board.getCellPtr(newX, newY)->setObject(&pacman);
			board.getCellPtr(newX, newY)->printCell();
		}
		else
		{// pacman die
			setLives(getLives() - 1);
			printData();
			board.getCellPtr(pacman.getX(), pacman.getY())->setObject(nullptr);
			board.getCellPtr(pacman.getX(), pacman.getY())->printCell();
			pacman.setX(pacman.getInitialX());
			pacman.setY(pacman.getInitialY());
			board.getCellPtr(pacman.getX(), pacman.getY())->setObject(&pacman);
			board.getCellPtr(pacman.getX(), pacman.getY())->printCell();
			
			if (saveMode)
				write_event_to_ResFile(this->getScore(),"pacman die");// pacman die

			if (fruit != nullptr)
			{
				board.getCellPtr(fruit->getX(), fruit->getY())->printContent();
				delete fruit;
				fruit = nullptr;
			}
			if (getLives() == 0)
			{// lost game
				return -1;
			}
			else
			{
				return 0;
			}
		}
	}

	if (turn % 20 == 0)
	{// fruit
		if (fruit == nullptr)
		{
			fruit = new Fruit;
			fruit->setLocation(board);
			board.getCellPtr(fruit->getX(), fruit->getY())->setObject(fruit);
			board.getCellPtr(fruit->getX(), fruit->getY())->printCell();
		}
	}
	if (fruit != nullptr)
	{
		if (turn % 40 == 0)
		{
			board.getCellPtr(fruit->getX(), fruit->getY())->setObject(nullptr);
			board.getCellPtr(fruit->getX(), fruit->getY())->printCell();
			delete fruit;
			fruit = nullptr;

			if (saveMode)
				write_fruit_to_file(0, 99, 99);//fruit dissapear
		}
		else
		{
			if (turn % 4 == 0)
			{
				moveResult = fruit->makeTurnFruit(board, fruit_direcion);

				if (saveMode)
					write_fruit_to_file(fruit_direcion, fruit->getInitialX(), fruit->getInitialY());

				if (moveResult == 1)
				{
					board.getCellPtr(fruit->getX(), fruit->getY())->setObject(fruit);
					fruit->print();
				}
				else if (moveResult == 2)
				{
					statusMap["Score"] = statusMap["Score"] + fruit->getValue();
					printData();
					delete fruit;
					fruit = nullptr;
				}
				else if (moveResult == 3)
				{
					delete fruit;
					fruit = nullptr;
				}
			}
			else
			{//fruit stay
				if (saveMode)
					write_fruit_to_file(0, fruit->getInitialX(), fruit->getInitialY());//fruit created
			}
		}
	}
	else
	{// fruit doesnt exsist
		if (saveMode)
			write_fruit_to_file(-1, 99, 99);//fruit dissapear
	}

	if (turn % 2 == 0)
	{// ghosts
		for (int i = 0; i < (int)ghostArr.size(); i++)
		{
			newX = ghostArr[i].getX();
			newY = ghostArr[i].getY();
			if (getDifficulty() == 3)
			{
				option = ghostArr[i].generateCell(pacman.getX(), pacman.getY(), board); // ghost dir
				if (option == 1)
				{
					newX = ghostArr[i].getX() - 1;
				}
				else if (option == 2)
				{
					newX = ghostArr[i].getX() + 1;
				}
				else if (option == 3)
				{
					newY = ghostArr[i].getY() - 1;
				}
				else
				{
					newY = ghostArr[i].getY() + 1;
				}

				if (saveMode)
					write_ghost_to_file(option, i+1);

				moveResult = ghostArr[i].makeMoveGhost(newX, newY, board);
			}
			else if (getDifficulty() == 2)
			{
				if (turn % 20 >= 0 && turn % 20 <= 5)
				{//turn 0-5
					if (turn % 20 == 0)
					{//turn 0
						ghostDirection[i] = generateRandomNumber(1, 4);
					}
					if (ghostDirection[i] == 1)
					{
						newX = newX - 1;
						moveResult = ghostArr[i].makeMoveGhost(newX, newY, board);
					}
					else if (ghostDirection[i] == 2)
					{
						newX = newX + 1;
						moveResult = ghostArr[i].makeMoveGhost(newX, newY, board);
					}
					else if (ghostDirection[i] == 3)
					{
						newY = newY - 1;
						moveResult = ghostArr[i].makeMoveGhost(newX, newY, board);
					}
					else
					{
						newY = newY + 1;
						moveResult = ghostArr[i].makeMoveGhost(newX, newY, board);
					}

					if (saveMode)
						write_ghost_to_file(ghostDirection[i], i + 1);

				}
				else
				{//smart
					option = ghostArr[i].generateCell(pacman.getX(), pacman.getY(), board);
					if (option == 1)
					{
						newX = ghostArr[i].getX() - 1;
					}
					else if (option == 2)
					{
						newX = ghostArr[i].getX() + 1;
					}
					else if (option == 3)
					{
						newY = ghostArr[i].getY() - 1;
					}
					else
					{
						newY = ghostArr[i].getY() + 1;
					}

					if (saveMode)
						write_ghost_to_file(option, i + 1);

					moveResult = ghostArr[i].makeMoveGhost(newX, newY, board);
				}
			}
			else
			{// difficulty 1
				if (turn % 20 == 0 || turn == 2)
				{ // turn 0 or turn 2
					ghostDirection[i] = generateRandomNumber(1, 4);
				}
				if (ghostDirection[i] == 1)
				{
					newX = newX - 1;
					moveResult = ghostArr[i].makeMoveGhost(newX, newY, board);
				}
				else if (ghostDirection[i] == 2)
				{
					newX = newX + 1;
					moveResult = ghostArr[i].makeMoveGhost(newX, newY, board);
				}
				else if (ghostDirection[i] == 3)
				{
					newY = newY - 1;
					moveResult = ghostArr[i].makeMoveGhost(newX, newY, board);
				}
				else
				{
					newY = newY + 1;
					moveResult = ghostArr[i].makeMoveGhost(newX, newY, board);
				}

				if (saveMode)
					write_ghost_to_file(ghostDirection[i], i + 1);
			}
			if (moveResult == 0)
			{
				board.getCellPtr(newX, newY)->setObject(&(ghostArr[i]));
				board.getCellPtr(newX, newY)->printCell();
			}
			else if (moveResult == 1)
			{
				delete fruit;
				fruit = nullptr;
				board.getCellPtr(newX, newY)->setObject(&(ghostArr[i]));
				board.getCellPtr(newX, newY)->printCell();
			}
			else if (moveResult == 2)
			{
				setLives(getLives() - 1);
				if (fruit != nullptr)
				{
					board.getCellPtr(fruit->getX(), fruit->getY())->printContent();
					delete fruit;
					fruit = nullptr;
				}
				printData();
				if (getLives() == 0)
				{
					return -1;
				}
				else
				{
					pacman.setX(pacman.getInitialX());
					pacman.setY(pacman.getInitialY());
					board.getCellPtr(pacman.getInitialX(), pacman.getInitialY())->setObject(&pacman);
					board.getCellPtr(pacman.getInitialX(), pacman.getInitialY())->printCell();
					board.getCellPtr(ghostArr[i].getInitialX(), ghostArr[i].getInitialY())->setObject(&(ghostArr[i]));
					board.getCellPtr(ghostArr[i].getInitialX(), ghostArr[i].getInitialY())->printCell();
				}
				return 0;
			}
		}
	}
	else
	{// ghost stay
		int i;
		if (saveMode)
		{
			for (i = 0; i < (int)ghostArr.size(); i++)
			{
				write_ghost_to_file(0, i + 1);
			}		
		}
	}
 
	
	Sleep(250);
	return 0;
}
bool Game::isValidMovementKey(char input)
{
	if ((input == 'w' || input == 'W') || (input == 'x' || input == 'X') || (input == 'a' || input == 'A') || (input == 'd' || input == 'D') || (input == 's' || input == 'S'))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Game::getNewCoord(char direction, int* x, int* y)
{
	if (direction == 'w' || direction == 'W')
	{
		*x = *x - 1;
	}
	else if (direction == 'a' || direction == 'A')
	{
		*y = *y - 1;
	}
	else if (direction == 'x' || direction == 'X')
	{
		*x = *x + 1;
	}
	else
	{
		*y = *y + 1;
	}
}
bool Game::checkWall(char direction, int x, int y)
{
	if (direction == 'w' || direction == 'W')
	{
		if (x==board.getTopBorder())
		{
			return false;
		}
		else if (board.getCellContent(x-1, y) == WALL)
		{
			return true;
		}
	}
	else if (direction == 'a' || direction == 'A')
	{
		if (y == board.getLeftBorder())
		{
			return false;
		}
		else if (board.getCellContent(x, y-1) == WALL)
		{
			return true;
		}
	}
	else if (direction == 'x' || direction == 'X')
	{
		if (x == board.getBottomBorder())
		{
			return false;
		}
		else if (board.getCellContent(x+1, y) == WALL)
		{
			return true;
		}
	}
	else
	{
		if (y == board.getRightBorder())
		{
			return false;
		}
		else if (board.getCellContent(x , y+1) == WALL)
		{
			return true;
		}
	}
	return false;
}
void Game::pauseGame()
{
	char  temp = 's';
	while (!_kbhit() || temp!= 27)
	{
		if (_kbhit())
		{
			temp = _getch();
			if (temp == 27)
			{
				return;
			}
			else
			{
				Sleep(250);
			}
		}
	}
}
void Game::load_screen_files()
{
	string path("./");
	string ext(".txt");

	for (auto& p : fs::recursive_directory_iterator(path))
	{
		if (p.path().extension() == ext)
			m_screenFiles.insert(p.path().stem().string());
	}

	set<string> ::iterator itr, temp_itr;
	string curr_fileName;
	string key1 = ".screen";
	itr = m_screenFiles.begin();

	while (itr != m_screenFiles.end())
	{
		curr_fileName = *itr;
		if (!(is_key_in_fileName(curr_fileName, key1)))
		{
			if (itr == m_screenFiles.begin())
			{
				m_screenFiles.erase(m_screenFiles.begin());
				itr = m_screenFiles.begin();
			}
			else
			{
				m_screenFiles.erase(itr);
				itr = temp_itr;
				itr++;
			}
		}
		else
		{
			temp_itr = itr;
			itr++;
		}
	}

	if (m_screenFiles.size() == 0)
	{
		cout << "No ~pacman_screen~ Files Found!" << endl;
		exit(1);
	}
	//menu();
}
void Game::load_screen(int screen_num)
{
	if (screen_num > (int)m_screenFiles.size())
	{// no more screens left

		system("cls");
		cout << "Game Finished!" << endl;
		system("pause");
	}
	else
	{
		this->setScreenNum(screen_num);
		this->clearGhostArr();
		this->setCrumbs(0);
		try
		{
			this->LoadFile(this->get_curr_screen_file());
		}
		catch (const string error)
		{
			throw error;
		}	

		system("cls");
		this->printBoard();
		this->printData();
	}
}
void Game::load_screen(const string& fileName)
{
	ifstream inFile;
	inFile.open(fileName + ".txt");

	if (!inFile)
	{
		cout << "Can't find file: " << fileName << endl;
		return;
	}
	else
	{
		this->setScreenNum(this->m_screenFiles.size());
		this->clearGhostArr();
		this->setCrumbs(0);
		this->LoadFile(fileName);

		system("cls");
		this->printBoard();
		this->printData();
	}
}
void Game::menu()
{
	printMainMenu();

	char c = EOF;
	while (c != '1' && c != '2' && c != '8' && c != '9')
		cin >> c;
	string fileName;
	switch (c)
	{
	case '1':
		receiveGhostLevel();
		system("cls");
		try
		{
			this->load_screen(this->getScreenNum());
		}
		catch (const string error)
		{
			cout << error;
			throw "Error loading Screen!";
		}
		
		this->setScore(0);
		this->setLives(3);
		startGame();
		break;
	case '2':
		fileName = receiveScreenFile();
		receiveGhostLevel();
		try
		{
			this->load_screen(fileName);
		}
		catch (const string error)
		{
			cout << error;
			throw "Error loading Screen!";
		}
		this->setScore(0);
		this->setLives(3);
		startGame();
		break;
	case '8':
		printControlsMenu();
		break;
	case '9':
		exit(1);
		break;
	default:
		break;
	}
}
void Game::printMainMenu()
{
	system("cls");

	string MainMenu = "\n\n";
	MainMenu += "              ~PACMAN PROJECT~		\n";
	MainMenu += "                 ofir & omer	\n\n\n";
	MainMenu += " Start a new game                       <1>\n";
	MainMenu += " Start a new game (specific screen)     <2>\n";
	MainMenu += " Controls Menu                          <8>\n";
	MainMenu += " Exit                                   <9>\n";


	cout << MainMenu;
}
void Game::receiveGhostLevel()
{
	system("cls");
	cout << "Choose the desired ghost level: " << endl <<
		"Bad        <1>" << endl <<
		"Good       <2>" << endl <<
		"Very Good  <3>" << endl;

	int choice = -1;
	while (choice == -1)
	{
		cin >> choice;

		if (choice != 1 && choice != 2 && choice != 3)
		{
			cout << "Wrong key, Please try again" << endl;
			choice = -1;
		}
	}
	statusMap["Difficulty"] = choice;
}
void Game::clearGhostArr()
{
	if (!ghostArr.empty())
		ghostArr.clear();
}
void Game::printData()
{
	gotoxy(m_dataLocation.second, m_dataLocation.first);
	cout << "Score: " << statusMap["Score"];

	gotoxy(m_dataLocation.second, m_dataLocation.first + 1);
	cout << "Lives: " << statusMap["Lives"];

	gotoxy(m_dataLocation.second, m_dataLocation.first + 2);
	cout << "Crumbs Left: " << board.getCrumbs() << ' ';
}
string Game::receiveScreenFile()
{
	system("cls");

	string res = "-1";
	ifstream inFile;

	while (res == "-1")
	{
		cout << "Please Enter a File Name: ";
		cin >> res;
		inFile.open(res + ".txt");

		if (!inFile)
		{
			cout << "Eror Loading file: " << res << endl;
			cout << " Press 1 to try again, 2 to go back to main menu or 3 to exit:" << endl;

			int choice = -1;
			while (choice == -1)
			{
				cin >> choice;

				if (choice != 1 && choice != 2 && choice != 3)
				{
					cout << "Wrong key, Please try again" << endl;
					choice = -1;
				}
			}

			if (choice == 1)
				res = "-1";
			else if (choice == 3)
				exit(1);
			else if (choice == 2)
			{
				system("cls");
				menu();
			}
		}
		else
		{
			inFile.close();
			return res;
		}
	}
}
void Game::printControlsMenu()
{
	system("cls");
	cout << "controls" << endl;
	cout << "Press <1> to go back to Main Menu, or <2> to EXIT: ";

	int choice = -1;
	while (choice == -1)
	{
		cin >> choice;

		if (choice != 1 && choice != 2)
		{
			cout << "Wrong key, Please try again" << endl;
			choice = -1;
		}
	}
	if (choice == 1)
		this->menu();
	else if (choice == 2)
		exit(1);
}
void Game::LoadFile(const string File_Name)
{
	if (currFileName.size() > 0)
		currFileName.clear();
	this->currFileName = delete_screen_from_fileName(File_Name);

	ifstream inFile;
	inFile.open(File_Name + ".txt");

	if (!inFile)
		throw "Error openning Screen File";

	int rows = getRowsFromFile(inFile);
	int cols = getColsFromFile(inFile);

	//Allocating a new gameBoard
	this->board.allocateCells(rows, cols);

	char c = EOF;
	char temp[1024];
	int i = 0, j = 0;
	inFile.seekg(0, ios::beg);//set coursor at the begining of the file


	while (!inFile.eof())
	{
		inFile.getline(temp, 1024);
		c = temp[j];
		while (c != '\0')
		{
			checkFileCharecter(c, i, j);// update Game data
			board.getCellPtr(i, j)->setContent(c);
			switch (c)// set object
			{
			case'@':
				board.getCellPtr(i, j)->setObject(&pacman);
				break;
			case'$':
				board.getCellPtr(i, j)->setObject(&ghostArr[ghostArr.size() - 1]);
				break;
			default:
			board.getCellPtr(i, j)->setObject(nullptr);
				break;
			}
			j++;
			c = temp[j];
		}
		i++;
		j = 0;
	}
	board.findBorders(this->m_dataLocation); // set gameBoard borders
	inFile.close();//Closing input File
	
    // ofir update exe3
	if (this->mode == SAVE_MODE)
	{
		try
		{
			this->open_appendix_file("steps");
			this->open_appendix_file("resault");

		}
		catch (const string error)
		{
			throw error;
		}
	}
	
	

}
int Game::getRowsFromFile(ifstream& inFile)
{
	int res = 0;
	char temp[1024];

	inFile.seekg(0, ios::beg);//set coursor at the begining of the file

	while (!inFile.eof())
	{
		if (!inFile.good()) { cout << "Error reading from File!" << endl; exit(1); }
		inFile.getline(temp, 1024);
		res++;
	}

	return res;
}
int Game::getColsFromFile(ifstream& inFile)
{//function gets an input file and returns the total amount of columns in the file

	int res = 0;
	int maxRes = 0;
	char temp[1024];
	bool flag = true;

	inFile.seekg(0, ios::end);//set coursor at the end of the file
	int size = inFile.tellg();
	inFile.seekg(0, ios::beg);//set coursor at the begining of the file

	while (!inFile.eof())
	{
		inFile.getline(temp, 1024);
		for (int i = 0; i < 1024 && flag == true; i++)
		{
			if (temp[i] != '\0')
				res++;
			else
				flag = false;
		}

		if (maxRes < res)
			maxRes = res;
		res = 0;
		flag = true;
	}


	return maxRes;
}
void Game::checkFileCharecter(char c, int row, int col)
{
	switch (c)
	{
	case '@':
		pacman.setInitialX(row);
		pacman.setInitialY(col);
		pacman.setX(row);
		pacman.setY(col);
		break;
	case '$':
		ghostArr.push_back(Ghost(row, col));
		break;
	case ' ':
		board.setCrumbs(board.getCrumbs() + 1);
		break;
	case '*':
		board.setCrumbs(board.getCrumbs() + 1);
		break;
	case '&':
		setDataLocation(row, col);
		break;
	default:
		break;
	}
}
const string Game::get_curr_screen_file()
{
	set<string> ::iterator itr;
	itr = m_screenFiles.begin();
	for (int i = 0; i < getScreenNum(); i++)
		itr++;


	return (*itr);
}


//Save mode files - ofir update exe3
void Game::open_appendix_file(const string& append)
{
	ofstream File;

	string newName = this->currFileName + "." + append + ".txt";
	File.open(newName);
	if (!File)
		throw "Error openning Save File";

	File.close();

}
void Game::write_pacman_to_file(char direction)
{
	ofstream saveFile;
	saveFile.open(this->currFileName + ".steps.txt", ios::app);//writing to end of file


	//saveFile << convert_int_to_string(this->getScore()) << ',';// write point of time to file
	saveFile << direction << ',';
	saveFile.close();
}
void Game::write_fruit_to_file(int direction, int x, int y)
{
	ofstream saveFile;
	saveFile.open(this->currFileName + ".steps.txt", ios::app);//writing to end of file

	if (x < 10)
	{
		if (y < 10)
		{
			if (direction == 0) // fruit doesnt move
				saveFile << ' ' << ',' << x << " ," << y << " ,";
			else if (direction == -1)// fruit doesnt exsist
				saveFile << 'M' << ',' << x << " ," << y << " ,";
			else
				saveFile << direction << ',' << x << " ," << y << " ,";
		}
		else
		{
			if (direction == 0) // fruit doesnt move
				saveFile << ' ' << ',' << x << " ," << y << ',';
			else if (direction == -1)// fruit doesnt exsist
				saveFile << 'M' << ',' << x << " ," << y << ',';
			else
				saveFile << direction << ',' << x << " ," << y << ',';
		}
	}
	else
	{
		if (y < 10)
		{
			if (direction == 0) // fruit doesnt move
				saveFile << ' ' << ',' << x << ',' << y << " ,";
			else if (direction == -1)// fruit doesnt exsist
				saveFile << 'M' << ',' << x << ',' << y << " ,";
			else
				saveFile << direction << ',' << x << ',' << y << " ,";
		}
		else
		{
			if (direction == 0) // fruit doesnt move
				saveFile << ' ' << ',' << x << ',' << y << ',';
			else if (direction == -1)// fruit doesnt exsist
				saveFile << 'M' << ',' << x << ',' << y << ',';
			else
				saveFile << direction << ',' << x << ',' << y << ',';
		}
	}

	
	saveFile.close();
}
void Game::write_ghost_to_file(int direction, int ghostNum)
{
	ofstream saveFile;
	saveFile.open(this->currFileName + ".steps.txt", ios::app);

	if (direction == 0)
	{// ghost doesnt move
		if (ghostNum == ghostArr.size())// last ghost
		{
			saveFile << ' ';
			saveFile << endl;
		}
		else
			saveFile << ' ' << ',';
	}
	else
	{
		if (ghostNum == ghostArr.size())// last ghost
		{
			saveFile << direction;
			saveFile << endl;
		}
		else
			saveFile << direction << ',';
	}
	

	saveFile.close();

}
void Game::write_event_to_ResFile(int pointOfTime, const string& event)
{
	ofstream ResFile;
	ResFile.open(this->currFileName + ".resault.txt", ios::app);

	ResFile << pointOfTime << ':' << event << endl;
	ResFile.close();
}
