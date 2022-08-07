/*Задание 5. Реализация игры «Что? Где? Когда?»
Что нужно сделать

Реализуйте простую версию интеллектуальной игры «Что? Где? Когда?».
Как происходит игра
В начале каждого хода игроки вращают волчок, то есть выбирают сектор на столе,
который сейчас играет. Всего таких секторов 13. Сектор выбирается так: с
клавиатуры вводится офсет (смещение) относительно текущего сектора на барабане.
Исходя из этого офсета вычисляется новый активный сектор, который и будет играть
в этом ходе. Если выпавший сектор уже играл, выбирает следующий неигравший за ним.
В начале всей игры стрелка установлена на первом секторе.
Как только играет какой-то из секторов, с него берётся письмо с вопросом — то есть
считывается из файла данного сектора. Вопрос показывается на экране.
После того как вопрос показан, от игрока ожидается ответ на него. Игрок вводит этот
ответ с помощью стандартного ввода. То, что он ввёл, сравнивается с ответом, который
хранится во втором файле, ассоциированном с активным сектором. Данный файл должен
содержать лишь одно слово-ответ.
Если ответ знатока-игрока был правильным, ему начисляется один балл. Если неверен,
то балл уходит телезрителям.
Игра продолжается до тех пор, пока или игрок, или зрители не наберут шесть баллов.
После этого называется победитель и программа заканчивает работу.*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

const std::string PATCH { "D:\\Skillbox\\Module_19\\Quiz" };
const int         NUMBER_OF_SECTORS { 13 };

//Выводит игровой стол с 13 секторами
void print_arr(bool* roulet) {
    
    for (int i = 0; i < NUMBER_OF_SECTORS; i++) {

        std::cout << *(roulet + i) << " ";
    }
    std::cout << std::endl;
}


//Ввод и проверка корректности ввода offset
int i_correst() {

    int count;
    std::string tmp;

    do
    {
        count = 0;
        std::getline(std::cin, tmp);
        for (auto p : tmp) {
            if (std::isdigit(p))
                count++;
        }
    } while (count != tmp.size());
    
    return std::stoi(tmp);
}

//Возвращает волный путь к файлу
std::string patch_filename(std::string filename) {

    return PATCH + "\\" + filename + ".txt";
}

//Возвращает строку содержащуюся ф открываемом файле
std::string ofile(std::string f_name) {

    std::ifstream ifs;

    std::string as = patch_filename(f_name);

    ifs.open(patch_filename(f_name));
    std::string tmp;

    if (ifs.is_open()) {

        std::getline(ifs, tmp);
        return tmp;
    }
    else
        return "File opening error";
}

//Получает любой положительный offset возвращает индекс сектора стола
int number(bool* roulet, int& offset, int& pos) {

    int count = 0;
    offset = (pos + offset) % NUMBER_OF_SECTORS;

    while (*(roulet + offset) == true && count < NUMBER_OF_SECTORS) {

        offset = (offset % NUMBER_OF_SECTORS) - 1;
        offset++;
        count++;                  
    }
    if (count != NUMBER_OF_SECTORS)
        *(roulet + offset) = true;

    pos = offset;
     
    return count == NUMBER_OF_SECTORS ? -1 : offset = offset % NUMBER_OF_SECTORS;
}

//Возвразает true если ответ игрока совпал с истиной
bool victory(std::string answer, int sectior, std::string* a) {

    if (answer == ofile(*(a + sectior)))
        return true;
    else
        return false;
}

//Смена игрока
void change_player(bool& player) {

    player = player == true ? false : true;
}

//Вывод строки файла
std::string show_qestion(std::string* q, int offset) {

    return ofile(*(q + offset));
}

//Итоговая функция
void result(bool* roulet, std::string* q, std::string* a) {

    bool player = true;
    int player_1 = 0; int player_2 = 0; int offset = 0; int pos = 0;    

    std::string tmp = player == true ? "1 player " : "2 player ";    
    
    std::cout << tmp << "Choose offset: ";
    offset = i_correst();
    
    offset = number(roulet, offset, pos);    

    while (offset != -1)
    {
        std::cout << show_qestion(q, offset);
        std::cout << std::endl;
        print_arr(roulet);
        std::string ans;
        std::cout << "Enter the answer \"Yes\" or \"No\": ";
        std::getline(std::cin, ans);
        
        if (player && (victory(ans, offset, a))) {

            player_1++;
            std::cout << "Correctly";
        }        
        else if (!player && (victory(ans, offset, a))) {

            player_2++;
            std::cout << "Correctly";
        }
        else
            std::cout << "Not right";             

        change_player(player);

        std::string tmp = player == true ? "1 player " : "2 player ";
        std::cout << std::endl << tmp << "Choose offset: ";
        offset = i_correst();
        offset = number(roulet, offset, pos);
    }

    if(player_1 == player_2)
        std::cout << "Draw!";
    if (player_1 > player_2)
        std::cout << "The victory of the first player!";
    else
        std::cout << "The victory of the second player!"; 
}

int main()
{
    bool roulet[13]{};

    std::string q[]{ "Question_1","Question_2","Question_3","Question_4","Question_5",
                     "Question_6","Question_7","Question_8","Question_9","Question_10",
                     "Question_11","Question_12","Question_13" };

    std::string a[]{ "Answer_1","Answer_2","Answer_3","Answer_4","Answer_5",
                     "Answer_6","Answer_7","Answer_8","Answer_9","Answer_10",
                     "Answer_11","Answer_12","Answer_13" };    
    
    result(roulet, q, a);    
}

    

    

    

    
    


