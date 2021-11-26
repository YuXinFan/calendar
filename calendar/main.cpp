//PREPEND BEGIN
#include <iostream>
#include <string>
//PREPEND END

//TEMPLATE BEGIN
//You just need to implement these two classes
class Gregorian{

private: 
    int year_;
    std::string month_;
    int day_;    
    int days_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    std::string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    int mmap[26*26*26+26*26+26]{-1};
    int MAX_year = 999999;
    int char32int(const char *month){
        return 26*26*(month[0]-'A')+26*(month[1]-'a')+ (month[2]-'a');
    }

    void initmmap(){
        for (int i = 0; i < sizeof(months)/sizeof(months[0]); i++) {
            mmap[char32int(months[i].c_str())] = i;
        }
    }

    int FebDays(int year){
        int leap = isLeapYear(year);
        return 29 * leap + (1-leap) * 28;
    }
    bool isLeapYear(int year){
        if ( year % 4 != 0){
            return false;
        }
        if ( year % 100 != 0){
            return true;
        }
        if ( year % 4000 != 0) {
            return true;
        }
        return false;
    }

public:
    Gregorian(){}
    Gregorian(int year, char* month, int day){
        year_ = year;
        month_ = std::string(month);
        day_ = day;
        initmmap();
    }
    void print_today() {
        std::cout << year_ <<" " << month_ << " " << day_ << std::endl;
    };
    void print_month() {
        std::string top    = "┌────┬────┬────┬────┬────┬────┬────┐";
        std::string title  = "│ Sun│ Mon│Tues│ Wed│Thur│ Fri│ Sat│";
        std::string mid    = "├────┼────┼────┼────┼────┼────┼────┤";
        std::string bottom = "└────┴────┴────┴────┴────┴────┴────┘";

        std::cout << top << "\n" << title << "\n" << mid << "\n";

        int c = year_ / 100;
        int y = year_ % 100;
        int m = char32int(month_.c_str());
        int w = (day_ + (13*m-1)/5 + y +y/4+ c/4-2 * c) % 7;
        std::string pad[42]{"  "};
        for (int i = w, j=0; i < w+days_month[m]; i++,j++){
            std::string num = std::to_string(j);
            if (j < 10){
                num = "0" + num;
            }
            pad[w] =  num ;
        }
        for (int i = 0; i < 6;  i++){
            std::cout << "│ " << pad[i*7] <<" │ " << pad[i*7+1] << "│ " << pad[i*7+2] << "│ " << pad[i*7+3] <<" │ " << pad[i*7+4] <<" │ " << pad[i*7+6] <<" │\n"; 
            if ( i == 5 ) {
                std::cout << bottom << std::endl;
            } else {
                std::cout << mid << "\n";
            }
        }

    };
    void print_year(){
        
    }
    bool go_to(int year, char* month, int day){
        int month_idx = mmap[char32int(month)];
        if (year >= 1 && year <= 9999){
            if (month_idx != -1) {
                if ( day < 0) {
                    return false;
                }
                if ( day <= days_month[month_idx]){
                    goto UPDATE;
                }else {
                    if (month_idx == 1 && isLeapYear(year) && day ==29){
                        goto UPDATE;
                    }
                }
            }
        }
        return false;
UPDATE: 
        year_ = year;
        month_ = month;
        day_ = day;
        return true;
    };
    bool pass_day(int num_days){
        int year = year_;
        int month_idx = char32int(month_.c_str());
        int day =  day_;
        
        days_month[1] = FebDays(year);
        for (int i = 1; i < month_idx; i++){
            num_days += days_month[i];
        }
        month_idx = 0; day = 1; num_days += day - 1;
        
        while ( true ){
            year = year_;
            bool leap = isLeapYear(year);
            if (leap){
                if ( num_days >= 366) {
                    pass_year(1);
                    num_days -= 366;
                }else{
                    break;
                }
            }else{
                if ( num_days >= 365 ){
                    pass_year(1);
                    num_days -= 365;
                }else{
                    break;
                }
            }
        }

        year = year_;
        days_month[1] = FebDays(year);
        month_idx = 0;
        while ( true ){
            if ( num_days >= days_month[month_idx])
            num_days -= days_month[month_idx];
            month_idx++;
        }
        day = num_days + 1;

        year_ = year;
        month_ = mmap[month_idx];
        day_ = day;
        return true;       
    };
    bool pass_month(int num_months){
        int years = num_months / 12;
        num_months = num_months % 12; 
        pass_year(years);

        int month_idx = char32int(month_.c_str());
        month_idx += num_months;
        month_idx = month_idx % 12;
        years = month_idx / 12;
        pass_year(years);

        month_ = months[month_idx].c_str();
        return true;
    };
    bool pass_year(int num_years){
        int year = year_;
        year += num_years;
        if (year > MAX_year){
            return false;
        }else {
            year_ = year;
            month_ = months[0].c_str();
            day_ = 1;
        } 
    };

};

class Shanghaitech:public Gregorian{
public:
    Shanghaitech():Gregorian(){}
    Shanghaitech(int year, char* month, int day):Gregorian(year, month, day){}
    
};

//TEMPLATE END

//APPEND BEGIN

// Use this main function
int main()
{
    int year, day, n;
    std::string calendar, f;
    char month[10];

    std::cin >> f;
    std::cin >> year >> month >> day;
    Shanghaitech date(year, month, day);
    Shanghaitech* S = &date;
    Gregorian* G = &date;
    std::cin >> calendar;
    std::cin >> f;
    while (!std::cin.eof()){
        if (f == "pass_day"){
            std::cin >> n;
            if (calendar=="G") G->pass_day(n); else S->pass_day(n);
        }
        else if (f == "pass_month"){
            std::cin >> n;
            if (calendar=="G") G->pass_month(n); else S->pass_month(n);
        }
        else if (f == "pass_year"){
            std::cin >> n;
            if (calendar=="G") G->pass_year(n); else S->pass_year(n);
        }
        else if (f == "print_today"){
            if (calendar=="G") G->print_today(); else S->print_today();
        }
        else if (f == "print_month"){
            if (calendar=="G") G->print_month(); else S->print_month();
        }
        else if (f == "print_year"){
            if (calendar=="G") G->print_year(); else S->print_year();
        }
        else if (f == "go_to"){
            std::cin >> year >> month >> day;
            if (calendar=="G") G->go_to(year, month, day); else S->go_to(year, month, day);
        }
        calendar = "";
        f = "";
        std::cin >> calendar;
        std::cin >> f;
    }
    return 0;
}
//APPEND END