# Hướng dẫn sử dụng

Menu: 1 Xem danh sách | 2 Thêm | 3 Sửa | 4 Xóa (xác nhận y/n) | 5 Tìm kiếm | 6 Tạo hóa đơn | 7 Hóa đơn & thống kê | 8 Lưu | 9 Tải lại | 0 Thoát (tự lưu).

## Định dạng file dữ liệu
- `data/phones.txt`: `Ma,Ten,Hang,Gia,TonKho` — mỗi dòng 1 sản phẩm, không dùng dấu phẩy trong tên.
- `data/invoices.txt`: `MaHD,Khach,Ngay,MaSP,TenSP,DonGia,SoLuong` — mỗi dòng 1 dòng hóa đơn; hóa đơn nhiều sản phẩm dùng chung MaHD.

## Quy tắc nghiệp vụ
- Mã sản phẩm là duy nhất; giá và tồn kho không được âm.
- Bán quá tồn kho → hóa đơn bị từ chối toàn bộ, tồn kho không đổi.
- Mã hóa đơn tự sinh: HD001, HD002, … tiếp nối sau mã lớn nhất đã tải.
