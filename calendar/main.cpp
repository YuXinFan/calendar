//PREPEND BEGIN
#include <iostream>
#include <string>
//PREPEND END

//TEMPLATE BEGIN
//You just need to implement these two classes
class Gregorian{
public:
    int tdays;   
    int MAX_DAY;
    int MIN_DAY;
private: 
    int MAX_YEAR;
    int MIN_YEAR;
    // common 
    int year_;
    std::string month_;
    int day_; 
    int days_round;
    // custom
    int days_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    std::string month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
public:
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
    bool format(){
        int tday = tdays;
        if ( tday > MAX_DAY || tday < MIN_DAY ){
            return false;
        }
        int days_next_year = 365;
        int year = 0;
        while ( tday > days_round ){
            year += 4000;
            tday -= days_round;
        }
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
        return true;
    }
public:
    Gregorian(int year, char* month, int day){
        MAX_YEAR = 999999;
        MIN_YEAR = 1;
        days_round = 4000 * 365 + 4000/4 - 4000/100 + 4000/400 - 4000/4000;
        MAX_DAY = 999999 * 365 + 999999/4 - 999999/100 + 999999/400 - 999999/4000;
        MIN_DAY = 1;
        tdays = 0;
    }
    void print_today() {
        std::cout << year_ <<" " << month_ << " " << day_ << std::endl;
    }
    void print_month() {
        std::string top    = std::string("┌────┬────┬────┬────┬────┬────┬────┐");
        
        std::string title  = std::string("│ Sun│ Mon│Tues│ Wed│Thur│ Fri│ Sat│");
        
        std::string mid    = std::string("├────┼────┼────┼────┼────┼────┼────┤");
        
        std::string bottom = std::string("└────┴────┴────┴────┴────┴────┴────┘");
        
        int w = (tdays - day_ + 1) % 7;
        int m = month2idx(month_);
        std::string pad[42];
        days_month[1] = daysFeb(year_);
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
        go_to(year, month[month_idx].c_str(), day);
        int w = tday % 7;
        std::string pad[12][42];
        days_month[1] = daysFeb(year);
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
                std::cout << month[i*3+j] <<"                                 ";
                if ( j < 2 ){
                    std::cout << " ";
                }
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
                                " │" ;
                    if ( j < 2){
                        std::cout << " ";
                    } 
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
    bool go_to(int year, const char* month, int day){
        int days_month_t[12] = {31, daysFeb(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int month_idx = month2idx(std::string(month));
        if (year >= MIN_YEAR && year <= MAX_YEAR){
            if (month_idx != -1) {
                if ( day > 0 && day <= days_month_t[month_idx]){
                    update(year, std::string(month), day);
                    return true;
                }
            }
        }
        return false;
    }
    bool pass_day(int num_days){
        std::cout<<"[---pass_day---"<<std::endl;
        print_today();
        std::cout<<"--- "<<num_days<<" days ---"<<std::endl;
        tdays += num_days;
        
        bool f = format();
        if (!f){
            tdays -= num_days;
        }
        print_today();
        std::cout<<"---pass_day---]"<<std::endl;
        return f;       
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
        bool f = go_to(year_ + years, month[month_idx].c_str(), 1);
        return f;
    }
    bool pass_year(int num_years){
        int year = year_;
        year += num_years;
        bool f = go_to(year, month[0].c_str(), 1);
        return f;
    }

};

class Shanghaitech:public Gregorian{
private:
    int MAX_YEAR;
    int MIN_YEAR;
    int year_;
    std::string month_;
    int day_;
    std::string month[9] = {"Sist", "Spst", "Slst", "Sem", "Sca", "Ims", "Ihuman", "Siais", "Ih"};
    std::string leap_month[9] = {"SIST", "SPST", "SLST", "SEM", "SCA", "IMS", "IHUMAN", "SIAIS", "IH"};
    int days_month[3][9] = {
            {39,41,40,39,41,40,39,41,40},
            {40,39,41,40,39,41,40,39,41},
            {41,40,39,41,40,39,41,40,39}
    };
    int days_year = 360;

    int years_table = 4000;
    int days_table[253] = {
    1459166, 1460780, 1460777, 1461956, 1460690, 1461962, 1461836, 1462107, 1460358, 1461974,
    1461909, 1462118, 1461471, 1462158, 1461754, 1461347, 1459691, 1461839, 1461869, 1462176,
    1461435, 1462303, 1461793, 1461516, 1460493, 1462188, 1461830, 1461675, 1460686, 1461715,
    1460608, 1460318, 1458605, 1461306, 1461869, 1462140, 1461471, 1462149, 1461790, 1461817,
    1460403, 1461993, 1461867, 1461950, 1460722, 1461835, 1460799, 1460647, 1459232, 1461219,
    1462147, 1461714, 1461072, 1461444, 1461190, 1460647, 1459579, 1460635, 1461386, 1460647,
    1459813, 1459877, 1459891, 1459003, 1458425, 1458719, 1461568, 1461872, 1462230, 1461390,
    1462197, 1461790, 1461718, 1460298, 1462288, 1461714, 1461805, 1460593, 1461808, 1460644,
    1460675, 1458702, 1462113, 1461745, 1461826, 1460721, 1461910, 1460763, 1460723, 1459156,
    1461605, 1460995, 1460725, 1459230, 1460538, 1459308, 1459158, 1458120, 1460517, 1462200,
    1461793, 1461426, 1460933, 1461428, 1460608, 1459851, 1460267, 1461557, 1460725, 1459928,
    1459840, 1460006, 1459198, 1458460, 1459121, 1461757, 1460647, 1460356, 1459449, 1460397,
    1459200, 1458807, 1458343, 1460556, 1459043, 1459119, 1457941, 1459079, 1458009, 1458132,
    1457940, 1460759, 1461959, 1461833, 1462147, 1461479, 1462071, 1461793, 1461110, 1461044,
    1462158, 1461793, 1461387, 1461011, 1461468, 1460568, 1459812, 1459888, 1462179, 1461908,
    1461516, 1460845, 1461713, 1460568, 1460084, 1459723, 1461715, 1460647, 1460358, 1459329,
    1460437, 1459200, 1458650, 1458171, 1462143, 1461790, 1461817, 1460572, 1461865, 1460602,
    1460680, 1459157, 1461913, 1460721, 1460764, 1459196, 1460649, 1459232, 1459159, 1458045,
    1461191, 1461149, 1460764, 1459503, 1460344, 1459579, 1459041, 1458195, 1459934, 1459891,
    1459082, 1458231, 1458865, 1458425, 1458133, 1457715, 1459584, 1462233, 1461754, 1461754,
    1460683, 1461718, 1460683, 1460438, 1459240, 1461805, 1460608, 1460554, 1459133, 1460635,
    1459122, 1459000, 1457939, 1461909, 1460723, 1460804, 1459116, 1460807, 1459155, 1459158,
    1458006, 1460742, 1459308, 1459082, 1458120, 1459171, 1458120, 1458093, 1457727, 1460952,
    1461468, 1460568, 1459891, 1459799, 1459890, 1459158, 1458385, 1459665, 1460006, 1459082,
    1458460, 1458873, 1458419, 1458174, 1457711, 1459287, 1460397, 1459082, 1458807, 1458331,
    1458845, 1458174, 1457861};

    int months_table[253] = {
    39522, 39482, 39482, 39451, 39484, 39451, 39454, 39445, 39492, 39451,
    39452, 39445, 39463, 39444, 39454, 39463, 39508, 39455, 39453, 39444,
    39463, 39441, 39453, 39459, 39487, 39444, 39452, 39455, 39481, 39454,
    39482, 39489, 39534, 39469, 39453, 39446, 39461, 39446, 39453, 39452,
    39487, 39450, 39451, 39449, 39479, 39452, 39477, 39481, 39517, 39470,
    39444, 39455, 39470, 39462, 39467, 39481, 39508, 39483, 39462, 39481,
    39502, 39501, 39500, 39523, 39538, 39533, 39462, 39453, 39443, 39464,
    39444, 39453, 39454, 39491, 39442, 39455, 39452, 39483, 39452, 39481,
    39480, 39531, 39447, 39454, 39452, 39479, 39450, 39478, 39479, 39519,
    39458, 39472, 39479, 39517, 39484, 39515, 39519, 39546, 39488, 39443,
    39453, 39461, 39475, 39461, 39482, 39501, 39492, 39458, 39479, 39499,
    39502, 39497, 39518, 39537, 39522, 39453, 39481, 39488, 39512, 39487,
    39518, 39528, 39541, 39483, 39522, 39520, 39551, 39521, 39549, 39546,
    39552, 39483, 39451, 39454, 39444, 39463, 39446, 39453, 39469, 39474,
    39444, 39453, 39462, 39473, 39460, 39483, 39502, 39503, 39444, 39450,
    39459, 39477, 39454, 39483, 39495, 39506, 39454, 39481, 39488, 39515,
    39486, 39518, 39532, 39546, 39446, 39453, 39452, 39483, 39451, 39482,
    39480, 39519, 39450, 39479, 39478, 39518, 39481, 39517, 39519, 39548,
    39469, 39468, 39478, 39510, 39489, 39508, 39522, 39544, 39500, 39500,
    39521, 39543, 39527, 39538, 39546, 39557, 39512, 39443, 39454, 39453,
    39481, 39454, 39480, 39486, 39518, 39452, 39482, 39483, 39520, 39481,
    39520, 39523, 39551, 39450, 39479, 39477, 39520, 39477, 39519, 39519,
    39549, 39479, 39515, 39521, 39546, 39519, 39546, 39547, 39557, 39476,
    39460, 39483, 39500, 39503, 39500, 39519, 39539, 39507, 39497, 39521,
    39537, 39527, 39538, 39545, 39557, 39518, 39487, 39521, 39528, 39541,
    39527, 39545, 39553};

    int month2idx(std::string s){
        if ( s == "Sist"){
            return 0;
        }else if ( s == "Spst"){
            return 1;
        }else if (s == "Slst"){
            return 2;
        }else if ( s=="Sem"){
            return 3;
        }else if ( s== "Sca"){
            return 4;
        }else if ( s== "Ims"){
            return 5;
        }else if (s=="Ihuman"){
            return 6;
        }else if ( s=="Siais"){
            return 7;
        }else if ( s=="Ih") {
            return 8;
        }
        return -1;
    }
    int leapMonth2idx(std::string s){
        if ( s == "SIST"){
            return 0;
        }else if ( s == "SPST"){
            return 1;
        }else if (s == "SLST"){
            return 2;
        }else if ( s=="SEM"){
            return 3;
        }else if ( s== "SCA"){
            return 4;
        }else if ( s== "IMS"){
            return 5;
        }else if (s=="IHUMAN"){
            return 6;
        }else if ( s=="SIAIS"){
            return 7;
        }else if ( s=="IH") {
            return 8;
        }
        return -1;
    }
    int daysMonth(int year, std::string month){
        int month_idx = month2idx(month);
        if (month_idx == -1){
            month_idx = leapMonth2idx(month);
        }
        __glibcxx_assert(month_idx > -1 && month_idx < 9);
        int days = days_month[(year + 2)%3][month_idx];
        return days;
    }
    int daysYear(int year){
        bool leap = isLeap(year);
        int days = days_year;
        if (leap){
            days += daysMonth(year, month[leapMonth(year)-1]);
        }
        return days;
    }
    int monthsYear(int year){
        bool leap = isLeap(year);
        return 10 * leap + (1-leap)*9;
    }
    int bitCount(int n){
        unsigned int count = 0;
        while (n) {
            count += n & 1;
            n >>= 1;
        }
        return count;
    }
    bool isLeap(int year){
        int count = bitCount(year);
        int mod = (year + count)%8;
        if (mod == 0){
            return true;
        } else {
            return false;
        }
    }
    int leapMonth(int year){
        int count = bitCount(year);
        int mod = (year - count) % 9  + 1;
        return mod;
    }
    void update(int year, std::string month, int day){
        year_ = year;
        month_ = month;
        day_ = day;
    }
    bool format(){
        int days = tdays;
        if (days > MAX_DAY || days < MIN_DAY){
            return false;
        }
        int year = 1;
        for (int i = 0; i < sizeof(days_table)/sizeof(int); i++){
            if (days > days_table[i]){
                year += years_table;
                days -= days_table[i];
            }else{
                break;
            }
        }
        int days_year = daysYear(year);
        while (days > days_year){
            year++;
            days -= days_year;
            days_year = daysYear(year);
        }
        int month_idx = 0;
        bool leap = isLeap(year);
        int leap_month_idx = leapMonth(year) -1 ;
        int days_month = daysMonth(year, month[month_idx]);
        bool in_leap_month = false;
        if ( leap ){
            while (days > days_month){
                if ( in_leap_month == false && leap_month_idx == month_idx){
                    in_leap_month = true;
                }else if ( in_leap_month == true && leap_month_idx == month_idx){
                    month_idx++;
                    in_leap_month = false;
                }else {
                    month_idx++;
                }
                days -= days_month;
                days_month = daysMonth(year, month[month_idx]);
            }
        }else {
            while (days > days_month){
                month_idx++;
                days -= days_month;
                days_month = daysMonth(year, month[month_idx]);
            }
        }
        int day = days;
        year_ = year;
        month_ = in_leap_month? leap_month[month_idx]:month[month_idx];
        day_ = day;
        //std::cout<<"Try format "<<tdays<<" to "<<year_<<" "<<month_<<" "<<day_<<std::endl;
        //std::cout<<"format "<<tdays<<" as "; print_today();
        return true;
    }
    void deformat(){
        std::cout<<"[S---deformat---"<<std::endl;
        print_today1();
        int year = 1;
        int day = day_;
        int days = 0;
        for (int i = 0; i < sizeof(days_table)/sizeof(int); i++){
            if (year_ > year + years_table){
                year += years_table;
                days += days_table[i];
            }else{
                break;
            }
        }
        while ( year < year_){
            days += daysYear(year);
            year++;
        }
        int month_idx = month2idx(month_);
        if (isLeap(year)){
            int leap_month_idx = leapMonth(year) -1 ;
            bool in_leap_month = false;
            if (month_idx == -1){
                month_idx = leapMonth2idx(month_);
                in_leap_month = true;
            }
            for (int i = 0; i < month_idx;){
                if ( i == leap_month_idx && in_leap_month == true){
                    days += daysMonth(year, month[i]);
                    in_leap_month = false;
                }else{
                    days += daysMonth(year, month[i]);
                    i++;
                }
            }
            if (month_idx == leap_month_idx){
                days += daysMonth(year, month[month_idx]);
            }
        }else{
            for (int i = 0; i < month_idx; i++){
                days += daysMonth(year, month[i]);
            }
        }
        days += day_;
        tdays = days;
        std::cout<<"--- "<<tdays<<" ---"<<std::endl;
        std::cout<<"---deformat---]"<<std::endl;
        Gregorian::format();
    }
public:
    Shanghaitech(int year, char* month, int day):Gregorian(year, month, day){
        MAX_YEAR = 1014560;
        MIN_YEAR = 1;
        bool f = go_to(year, month,day);
        std::cout<<"Init MAX_DAY: "<<MAX_DAY<<" MIN_DAY: "<<MIN_DAY<<std::endl;
        std::cout<<f<<" Init Shanghaitech with "<<year<<" " <<month<<" "<<day<<" as "<< tdays <<" days"<<std::endl;
    }
    void print_today1() {
        std::cout << year_ <<" " << month_ << " " << day_ << std::endl;
    };
    void print_today() {
        format();
        std::cout << year_ <<" " << month_ << " " << day_ << std::endl;
    };
    void print_month() {
        std::string top    = std::string("┌────┬────┬────┬────┬────┬────┬────┐");
        
        std::string title  = std::string("│ Sun│ Mon│Tues│ Wed│Thur│ Fri│ Sat│");
        
        std::string mid    = std::string("├────┼────┼────┼────┼────┼────┼────┤");
        
        std::string bottom = std::string("└────┴────┴────┴────┴────┴────┴────┘");
        format();
        int w = (tdays - day_ + 1) % 7;
        int m = month2idx(month_);
        int days = daysMonth(year_, month_);
        std::string pad[49];
        for (int i = 0; i < 49; i++) { pad[i] = "  ";}
        int j = 1;
        for (int i = w; i < w+days; i++){
            std::string num = std::to_string(j);
            if (j < 10){
                num = std::string("0") + num;
            }
            pad[i] =  num ;
            j++;
        }
        std::cout << month_ <<"                                 " << std::endl;
        std::cout << top << "\n" << title << "\n" << mid << std::endl;
        for (int i = 0; i < 7;  i++){
            std::cout << "│ " << pad[i*7] <<" │ " << pad[i*7+1] << " │ " << pad[i*7+2] << " │ " << pad[i*7+3] <<" │ " << pad[i*7+4] <<" │ " << pad[i*7+5] <<" │ " << pad[i*7+6] <<" │" << std::endl; 
            if ( i == 5 ) {
                std::cout << bottom << std::endl;
            }else{
                std::cout << mid << std::endl;
            }
        }
    }
    void print_year(){
        format();
        std::string top    = std::string("┌────┬────┬────┬────┬────┬────┬────┐") ;
        top = top + " " + top + " " + top;
        std::string title  = std::string("│ Sun│ Mon│Tues│ Wed│Thur│ Fri│ Sat│");
        title = title + " " + title + " " + title;
        std::string mid    = std::string("├────┼────┼────┼────┼────┼────┼────┤");
        mid = mid + " " + mid + " " + mid;
        std::string bottom = std::string("└────┴────┴────┴────┴────┴────┴────┘");
        bottom = bottom + " " + bottom + " " + bottom;
        int year = year_;
        std::string montht = month_;
        int day = day_;
        go_to(year, month[0].c_str(), 1);
        int tday = tdays;
        go_to(year, montht.c_str(), day);
        int w = tday % 7;
        std::string pad[10][49];
        for (int i = 0; i < 10; i++) { 
            for (int j = 0; j < 49; j++){
                pad[i][j] = std::string("  ");
            }
        }
        int days[10];
        int j = 0;
        for (int i = 0; i < 10; i++){
            if (isLeap(year) && leapMonth(year) -1 == i){
                    days[j] = days_month[year%3][j];
                    days[j+1] = days_month[year%3][j];
                    j++;
            }else{
                days[j] = days_month[year%3][j];
            }
            j++;
        }
        if (! isLeap(year)){
            days[9] = 0;
        }
        for (int m = 0; m < 10; m++){
            int j = 1;
            for (int i = w; i < w+days[m]; i++){
                std::string num = std::to_string(j);
                if (j < 10){
                    num = std::string("0") + num;
                }
                pad[m][i] =  num ;
                j++;
            }
            w = (w + days[m]) % 7;
        }

        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                std::cout << month[i*3+j] <<"                                 ";
                if ( j < 2 ){
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
            std::cout << top << "\n" << title << "\n" << mid << std::endl;
            for (int k = 0; k < 7;  k++){
                for (int j = 0; j < 3; j++){
                    std::cout << "│ " << pad[i*3+j][k*7] << \
                                " │ " << pad[i*3+j][k*7+1] << \
                                " │ " << pad[i*3+j][k*7+2] << \
                                " │ " << pad[i*3+j][k*7+3] << \
                                " │ " << pad[i*3+j][k*7+4] << \
                                " │ " << pad[i*3+j][k*7+5] << \
                                " │ " << pad[i*3+j][k*7+6] << \
                                " │" ;
                    if ( j < 2){
                        std::cout << " ";
                    } 
                }
                std::cout << std::endl;
                if ( k == 6 ) {
                    std::cout << bottom << std::endl;
                }else{
                    std::cout << mid << std::endl;
                }
            }
        }
        if (isLeap(year)){
            std::string mon = days[9] == days[8] ? leap_month[8] : month[8];
            std::cout << mon <<"                                 " << std::endl;
            std::cout << top << "\n" << title << "\n" << mid << std::endl;
            for (int i = 0; i < 7;  i++){
                std::cout << "│ " << pad[i*7] <<" │ " << pad[i*7+1] << " │ " << pad[i*7+2] << " │ " << pad[i*7+3] <<" │ " << pad[i*7+4] <<" │ " << pad[i*7+5] <<" │ " << pad[i*7+6] <<" │" << std::endl; 
                if ( i == 5 ) {
                    std::cout << bottom << std::endl;
                }else{
                    std::cout << mid << std::endl;
                }
            }
        }
    }
    bool go_to(int year, const char* month, int day){
        int month_idx = month2idx(std::string(month));
        bool leap_month = false;
        if (month_idx == -1){
            month_idx = leapMonth2idx(std::string(month));
            leap_month = true;
        }
        if (year >= MIN_YEAR && year <= MAX_YEAR){
            if (month_idx != -1) {
                if ( day > 0 && day <= daysMonth(year, std::string(month))){
                    std::cout<<"Log Update: "<<year<<month<<day<<std::endl;
                    update(year, month, day);
                    deformat();
                    Gregorian::format();
                    return true;
                }
            }
        }
        return false;
    }
    bool pass_day(int num_days){
        bool f = Gregorian::pass_day(num_days);
        if (f){
            format();
        }
        return f;
    }
    bool pass_month(int num_months){
        std::cout<<"[---pass_month---"<<std::endl;
        format();
        print_today1();
        std::cout<<"--- "<<num_months<<" month ---"<<std::endl;
        int year = 1;
        int months = 0;
        for (int i = 0; i < sizeof(months_table)/sizeof(int);i++){
            if(year < year_ - years_table) {
                months += months_table[i];
                year += years_table;
            }else {
                break;
            }
        }
        while (year < year_){
            months += monthsYear(year);
            year++;
        }
        int month_idx = month2idx(month_);
        if (isLeap(year_)){
            int leap_month_idx = leapMonth(year_)-1;
            if (month_idx == -1 ){
                months += num_months + leap_month_idx + 1; 
            }else if (month_idx > leap_month_idx){
                months += num_months + month_idx + 1; 
            }else{
                months += num_months + month_idx;
            }
        }else{
            months += num_months + month_idx;
        }

        year = 1;
        for (int i = 0; i < sizeof(months_table)/sizeof(int);i++){
            if(months > months_table[i]) {
                months -= months_table[i];
                year += years_table;
            }else {
                break;
            }
        }
        while (months > monthsYear(year)){
            months -= monthsYear(year);
            year++;
        }
        month_idx = months-1;
        bool leap = isLeap(year);
        std::string m = "";
        if (leap){
            int leap_month_idx = leapMonth(year)-1;
            if (month_idx > leap_month_idx){
                month_idx--;
            }
            if (month_idx == leap_month_idx){
                m = leap_month[month_idx];
            }else{
                m = month[month_idx];
            }
        }else{
            m = month[month_idx];
        }
        std::cout<<"Log: "<<year<<m<<1<<std::endl;
        bool  f = go_to(year, m.c_str(), 1);
        print_today1();
        std::cout<<"---pass_month---] "<<f<<std::endl;
        return f;
    }
    bool pass_year(int num_years){
        format();
        std::cout<<"[---pass_year---"<<std::endl;
        print_today1();
        std::cout<<"--- "<<num_years<<" year ---"<<std::endl;
        bool f = go_to(year_ + num_years, month[0].c_str(), 1);
        print_today1();
        std::cout<<"---pass_year---] "<<f<<std::endl;
        return f;
    }
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
// int main()
// {
//     int year, day, n;
//     std::string calendar, f;
//     char month[12];

//     std::cin >> calendar;
//     std::cin >> year >> month >> day;
//     Shanghaitech date(year, month, day);
//     Shanghaitech* S = &date;
//     Gregorian* G = &date;
//     std::cin >> f;
//     while (!std::cin.eof()){
//         if (f == "pass_day"){
//             std::cin >> n;
//              G->pass_day(n); 
//         }
//         else if (f == "pass_month"){
//             std::cin >> n;
//             G->pass_month(n); 
//         }
//         else if (f == "pass_year"){
//             std::cin >> n;
//             G->pass_year(n); 
//         }
//         else if (f == "print_today"){
//              G->print_today(); 
//         }
//         else if (f == "print_month"){
//             G->print_month(); 
//         }
//         else if (f == "print_year"){
//              G->print_year();
//         }
//         else if (f == "go_to"){
//             std::cin >> year >> month >> day;
//             G->go_to(year, month, day);
//         }
//         f = "";
//         std::cin >> f;
//     }
//     return 0;
// }
//APPEND END