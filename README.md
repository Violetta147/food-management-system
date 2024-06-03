# PBL1

Food management system

## Quick run

```bash
./run.sh

# Or
bash run.sh
```

## Note

header should include `#pragma once`

```mermaid
flowchart TD
    Start([Bắt đầu]) --> InputX["Nhập X để thoát chương trình"]
    InputX --> Enter["enter()"]
    Enter --> ModeCheck{"toupper(mode) == 'A'"}
    
    ModeCheck -- Có --> AdminPassword["Nhập mật khẩu Quản trị viên"]
    AdminPassword --> PassCheck{"Mật khẩu đúng không?"}
    PassCheck -- Có --> AccessGranted["TRUY CẬP THÀNH CÔNG"]
    AccessGranted --> ReadMenu["readMenu('Food.txt')"]
    ReadMenu --> AdminModeLoop{{"Chế độ Quản trị"}}
    
    PassCheck -- Không --> RetryCounter["Số lần thử < 4"]
    RetryCounter -- Có --> AdminPassword
    RetryCounter -- Không --> ExitProgram["Thoát chương trình"]
    
    AdminModeLoop --> PrintAdminMenu["printMenuAdmin()"]
    PrintAdminMenu --> AdminAns["Ans()"]
    AdminAns --> MoveCheck{"toupper(move)"}
    
    MoveCheck -- "D" --> Erase["erase()"] --> AdminModeLoop
    MoveCheck -- "A" --> Extend["extend()"] --> AdminModeLoop
    MoveCheck -- "C" --> Custom["custom()"] --> AdminModeLoop
    MoveCheck -- "S" --> Statistics["Statistics()"] --> AdminModeLoop
    
    AdminModeLoop --> ExitAdminMode["Thoát Chế độ Quản trị"] --> Start
    
    ModeCheck -- Không --> CustomerCheck{"toupper(mode) == 'C'"}
    CustomerCheck -- Có --> WorkingDay["Nhập ngày làm việc"]
    WorkingDay --> DayStatus{"Ngày đã kết thúc?"}
    DayStatus -- Có --> NoAccess["Không thể truy cập để đặt món"] --> Start
    DayStatus -- Không --> CustomerMode{{"Chế độ Khách hàng"}}
    
    CustomerMode --> CustomerOption{"Chọn tùy chọn"}
    CustomerOption -- "Đặt hàng và Thanh toán" --> OrderPay["Đặt hàng và Thanh toán"]
    CustomerOption -- "Hóa

```
