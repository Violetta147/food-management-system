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
    BatDau([Bắt đầu]) --> NhapX["Nhập X để thoát chương trình"]
    NhapX --> XacNhan["enter()"]
    XacNhan --> KiemTraCheDo{"toupper(mode) == 'A'"}
    
    KiemTraCheDo -- Có --> NhapMatKhauAdmin["Nhập mật khẩu Quản trị viên"]
    NhapMatKhauAdmin --> KiemTraMatKhau{"Mật khẩu đúng không?"}
    KiemTraMatKhau -- Có --> TruyCapThanhCong["TRUY CẬP THÀNH CÔNG"]
    TruyCapThanhCong --> DocThucDon["readMenu('Food.txt')"]
    DocThucDon --> VongLapCheDoAdmin{{"Chế độ Quản trị"}}
    
    KiemTraMatKhau -- Không --> DemSoLanThu["Số lần thử < 4"]
    DemSoLanThu -- Có --> NhapMatKhauAdmin
    DemSoLanThu -- Không --> ThoatChuongTrinh["Thoát chương trình"]
    
    VongLapCheDoAdmin --> InMenuAdmin["printMenuAdmin()"]
    InMenuAdmin --> TraLoiAdmin["Ans()"]
    TraLoiAdmin --> KiemTraDiChuyen{"toupper(move)"}
    
    KiemTraDiChuyen -- "D" --> XoaMon["erase()"] --> VongLapCheDoAdmin
    KiemTraDiChuyen -- "A" --> ThemMon["extend()"] --> VongLapCheDoAdmin
    KiemTraDiChuyen -- "C" --> DoiThongTin["custom()"] --> VongLapCheDoAdmin
    KiemTraDiChuyen -- "S" --> ThongKe["Statistics()"] --> VongLapCheDoAdmin
    
    VongLapCheDoAdmin --> ThoatCheDoAdmin["Thoát Chế độ Quản trị"] --> BatDau
    
    KiemTraCheDo -- Không --> KiemTraKhachHang{"toupper(mode) == 'C'"}
    KiemTraKhachHang -- Có --> NhapNgayLamViec["Nhập ngày làm việc"]
    NhapNgayLamViec --> TinhTrangNgay{"Ngày đã kết thúc?"}
    TinhTrangNgay -- Có --> KhongTruyCap["Không thể truy cập để đặt món"] --> BatDau
    TinhTrangNgay -- Không --> CheDoKhachHang{{"Chế độ Khách hàng"}}
    
    CheDoKhachHang --> LuaChonKhachHang{"Chọn tùy chọn"}
    LuaChonKhachHang -- "Đặt hàng và Thanh toán" --> DatHangVaThanhToan["Đặt hàng và Thanh toán"]
    LuaChonKhachHang -- "Hóa đơn chưa thanh toán" --> HoaDonChuaThanhToan["Hóa đơn chưa thanh toán"]
    LuaChonKhachHang -- "Thoát về Bảng điều khiển chính" --> ThoatVeBangDieuKhien["Thoát về Bảng điều khiển chính"] --> BatDau
    LuaChonKhachHang -- "Kết thúc ngày" --> KetThucNgay["Kết thúc ngày"]
    
    HoaDonChuaThanhToan --> ThemDonHang["Thêm đơn vào hóa đơn chưa thanh toán"]
    HoaDonChuaThanhToan --> ThanhToanHoaDon["Thanh toán hóa đơn"]
    ThemDonHang --> CheDoKhachHang
    ThanhToanHoaDon --> CheDoKhachHang
    
    KetThucNgay --> InThongKeNgay["In thống kê trong ngày"]
    InThongKeNgay --> BatDau

    CheDoKhachHang --> LuaChonKhachHang
    KiemTraKhachHang -- Không --> BatDau
    
    BatDau --> KetThuc([Kết thúc])


```
