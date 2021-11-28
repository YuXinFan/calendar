//PREPEND BEGIN
#include <iostream>
#include <string>
//PREPEND END

//TEMPLATE BEGIN
//You just need to implement these two classes
class Gregorian{
private: 
    // common 
    int year_;
    std::string month_;
    int day_; 
    int tdays;   
    int MAX_DAY;
    int MIN_DAY;
    int MAX_YEAR;
    int MIN_YEAR;
    // custom
    int days_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    std::string month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    int month2idx(std::string month){
        if (month == "Jan"){
            return 0;
        }else if (month == "Feb"){
            return 1;
        }else if (month == "Mar"){
            return 2;
        }else if (month == "Apr"){
            return 3;
        }else if (month == "May"){
            return 4;
        }else if (month == "Jun"){
            return 5;
        }else if (month == "Jul"){
            return 6;
        }else if (month == "Aug"){
            return 7;
        }else if (month == "Sep"){
            return 8;
        }else if (month == "Oct"){
            return 9;
        }else if (month == "Nov"){
            return 10;
        }else if (month == "Dec"){
            return 11;
        }
        return -1;
    }
    int daysFeb(int year){
        int leap = isLeap(year);
        return 29 * leap + (1-leap) * 28;
    }
    bool isLeap(int year){
        if ( year % 4000 == 0){
            return false;
        }
        if ( year % 400 == 0){
            return true;
        }
        if ( year % 100 == 0) {
            return false;
        }
        if ( year % 4 == 0) {
            return true;
        }else {
            return false;
        }
    }
    void update(int year, std::string month, int day){
        year_ = year;
        month_ = month;
        day_ = day;

        days_month[1] = daysFeb(year); 
        deformat();
    }
    void updateOnly(int year, std::string month, int day){
        year_ = year;
        month_ = month;
        day_ = day;

        days_month[1] = daysFeb(year); 
    }
    int daysYear(int year){
        bool leap = isLeap(year);
        return 366 * leap + (1-leap) * 365;
    }
    void deformat(){
        int year = year_;
        int month_idx = month2idx(month_);
        int day = day_;
        int tday = day;
        days_month[1] = daysFeb(year);
        for (int i = 0; i < month_idx; i++){
            tday += days_month[i];
        }
        year -= 1;
        int leap_days = year/4 - year/100 + year/400 -year/4000;
        tday = tday + leap_days + year * 365;
        tdays = tday;
    }
    void format(){
        int tday = tdays;
        int days_next_year = 365;
        int year = 0;
        while (tday > days_next_year){
            tday -= days_next_year;
            year++;
            days_next_year = daysYear(year+1);
        }
        year++;
        int month_idx = 0;
        days_month[1] = daysFeb(year);
        while (tday > days_month[month_idx]){
            tday -= days_month[month_idx];
            month_idx++;
        }
        update(year, month[month_idx], tday);
    }
public:
    Gregorian(){}
    Gregorian(int year, char* month, int day){
        MAX_YEAR = 999999;
        MIN_YEAR = 1;
        update(year, std::string(month), day);
    }
    void print_today() {
        std::cout << year_ <<" " << month_ << " " << day_ << std::endl;
    }
    void print_month() {
        std::string top    = std::string("┌────┬────┬────┬────┬────┬────┬────┐");
        
        std::string title  = std::string("│ Sun│ Mon│Tues│ Wed│Thur│ Fri│ Sat│");
        
        std::string mid    = std::string("├────┼────┼────┼────┼────┼────┼────┤");
        
        std::string bottom = std::string("└────┴────┴────┴────┴────┴────┴────┘");
        
        int w = (tdays - day_ + 1)% 7;
        int m = month2idx(month_);
        std::string pad[42];
        for (int i = 0; i < 42; i++) { pad[i] = "  ";}
        int j = 1;
        for (int i = w; i < w+days_month[(m)%12]; i++){
            std::string num = std::to_string(j);
            if (j < 10){
                num = std::string("0") + num;
            }
            pad[i] =  num ;
            j++;
        }
        std::cout << month_ <<"                                 " << std::endl;
        std::cout << top << "\n" << title << "\n" << mid << std::endl;
        for (int i = 0; i < 6;  i++){
            std::cout << "│ " << pad[i*7] <<" │ " << pad[i*7+1] << " │ " << pad[i*7+2] << " │ " << pad[i*7+3] <<" │ " << pad[i*7+4] <<" │ " << pad[i*7+5] <<" │ " << pad[i*7+6] <<" │" << std::endl; 
            if ( i == 5 ) {
                std::cout << bottom << std::endl;
            }else{
                std::cout << mid << std::endl;
            }
        }

    }
    void print_year(){
        std::string top    = std::string("┌────┬────┬────┬────┬────┬────┬────┐") ;
        top = top + " " + top + " " + top;
        std::string title  = std::string("│ Sun│ Mon│Tues│ Wed│Thur│ Fri│ Sat│");
        title = title + " " + title + " " + title;
        std::string mid    = std::string("├────┼────┼────┼────┼────┼────┼────┤");
        mid = mid + " " + mid + " " + mid;
        std::string bottom = std::string("└────┴────┴────┴────┴────┴────┴────┘");
        bottom = bottom + " " + bottom + " " + bottom;

        int year = year_;
        int month_idx = month2idx(month_);
        int day = day_;
        pass_month(-month_idx);
        int tday = tdays;
        update(year, month[month_idx], day);
        int w = tday % 7;
        std::string pad[12][42];
        for (int i = 0; i < 12; i++) { 
            for (int j = 0; j < 42; j++){
                pad[i][j] = std::string("  ");
            }
        }
        for (int m = 0; m < 12; m++){
            int j = 1;
            for (int i = w; i < w+days_month[(m)%12]; i++){
                std::string num = std::to_string(j);
                if (j < 10){
                    num = std::string("0") + num;
                }
                pad[m][i] =  num ;
                j++;
            }
            w = (w + days_month[m]) % 7;
        }
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 3; j++){
                std::cout << month[i*3+j] <<"                                 "<<" ";
            }
            std::cout << std::endl;
            std::cout << top << "\n" << title << "\n" << mid << std::endl;
            for (int k = 0; k < 6;  k++){
                for (int j = 0; j < 3; j++){
                    std::cout << "│ " << pad[i*3+j][k*7] << \
                                " │ " << pad[i*3+j][k*7+1] << \
                                " │ " << pad[i*3+j][k*7+2] << \
                                " │ " << pad[i*3+j][k*7+3] << \
                                " │ " << pad[i*3+j][k*7+4] << \
                                " │ " << pad[i*3+j][k*7+5] << \
                                " │ " << pad[i*3+j][k*7+6] << \
                                " │ " ; 
                    
                }
                std::cout << std::endl;
                if ( k == 5 ) {
                    std::cout << bottom << std::endl;
                }else{
                    std::cout << mid << std::endl;
                }
            }
            
        }
        
        
    }
    bool go_to(int year, char* month, int day){
        int days_month_t[12] = {31, daysFeb(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int month_idx = month2idx(std::string(month));
        if (year >= MIN_YEAR && year <= MAX_YEAR){
            if (month_idx != -1) {
                if ( day < 0) {
                    return false;
                }
                if ( day <= days_month_t[month_idx]){
                    update(year, std::string(month), day);
                    return true;
                }
            }
        }
        return false;
    }
    bool pass_day(int num_days){
        tdays += num_days;

        format();

        return true;       
    }
    bool pass_month(int num_months){
        int month_idx = month2idx(month_);
        month_idx += num_months;
        int years = month_idx / 12;
        month_idx = month_idx % 12; 
        if (month_idx < 0) {
            years -= 1;
            month_idx += 12;
        }
        update(year_ + years, month[month_idx], 1);
        return true;
    }
    bool pass_year(int num_years){
        int year = year_;
        year += num_years;
        if (year > MAX_YEAR){
            return false;
        }else {
            update(year, month[0], 1);
            return true;
        } 
    }

};

class Shanghaitech:public Gregorian{
// private:
//     std::string month[9] = {"Sist", "Spst", "Slst", "Sem", "Sca", "Ims", "Ihuman", "Siais", "Ih"};
//     std::string leap_month[9] = {"SISI", "SPST", "SLST", "SEM", "SCA", "IMS", "IHUMAN", "SIAIS", "IH"};
//     int month2idx(std::string s){
//         if ( s == "Sist"){
//             return 0;
//         }else if ( s == "Spst"){
//             return 1;
//         }else if (s == "Slst"){
//             return 2;
//         }else if ( s=="Sem"){
//             return 3;
//         }else if ( s== "Sca"){
//             return 4;
//         }else if ( s== "Ims"){
//             return 5;
//         }else if (s=="Ihuman"){
//             return 6;
//         }else if ( s=="Siais"){
//             return 7;
//         }else if ( s=="Ih") {
//             return 8;
//         }
//         return -1;
//     }
//     int daysMonth(int year, std::string month){
//         int days = 39 + (((10 * year) - month2idx(month) - 1) % 3 + 3 ) % 3;
//         return days;
//     }
//     int daysYear(int year){
//         // bool leap = isLeap(year);
//         // int days = 0;
//         // for (int i = 0; i < 9; i++) {
//         //     days += daysMonth(year, month[i]);
//         // }
//         // if (leap){
//         //     days += daysMonth(year, leapMonth(year));
//         // }
//         // return days;
//         return 0;
//     }
//     int bitCount(int n){
//         unsigned int count = 0;
//         while (n) {
//             count += n & 1;
//             n >>= 1;
//         }
//         return count;
//     }
//     bool isLeap(int year){
//         int count = bitCount(year);
//         int mod = (year + count)%8;
//         if (mod == 0){
//             return true;
//         } else {
//             return false;
//         }
//     }
//     int leapMonth(int year){
//         int count = bitCount(year);
//         int mod = ((year - count) % 9 + 9) % 9 + 1;
//         return mod;
//     }
//     void format(){
        // int year = 1;
        // int days = tdays;
        // int days_year = daysYear(year);
        // while (tdays > days_year){
        //     year++;
        //     days -= days_year;
        //     days_year = daysYear(year);
        // }
        // int month_idx = 0;
        // bool leap = isLeap(year);
        // int leap_month = leapMonth(year);
        // int days_month = daysMonth(year, month_idx);
        // bool in_leap_month = false;
        // while (days > days_month){
        //     if (leap){
        //         if ( in_leap_month == false && leap_month == month_idx){
        //             in_leap_month == true;
        //         }else if ( in_leap_month == true && leap_month == month_idx){
        //             month_idx++;
        //         }else {
        //             month_idx++;
        //         }
        //     }else{
        //         month_idx++;
        //     }
        //     days -= days

        // }
        // int day = days;
        // update(year, month[month_idx], day);
    // }
    // void deformat(){
        // int year = year_;
        // int month_idx = month2idx(month_);
        // int day = day_;
        // int days = 0
        // if (isLeap(year)){
        //     int leap_month = leapMonth(year);
        //     if (leap_month )

        // }
        // while ( year > 1){
        //     days += daysYear(year);
        //     year--;
        // }
        // while ( month_idx > 0){
        //     days += daysMonth(1, month[month_idx]);
        // }
//     }
public:
    Shanghaitech():Gregorian(){}
    Shanghaitech(int year, char* month, int day):Gregorian(year, month, day){}
    // void print_today() {
    //     std::cout << year_ <<" " << month_ << " " << day_ << std::endl;
    // };
    // void print_month() {
    // }
    // void print_year(){
    //     std::cout << "Year Table" << std::endl;
    //     print_today();
    // }
    // bool go_to(int year, char* month, int day){
    //     return true;
    // }
    // bool pass_day(int num_days){
    //     return true;
    // }
    // bool pass_month(int num_months){
    //     return true;
    // }
    // bool pass_year(int num_years){
    //     return true;
    // }
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