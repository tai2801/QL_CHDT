# Báo cáo kiểm thử — Quản lý cửa hàng bán điện thoại (QL_CHDT)

Ngày kiểm thử: 25/03/2023 · Môi trường: g++ 11.3.0 (MinGW-w64 / Ubuntu 22.04), `-std=c++17 -Wall -Wextra -O2`

## 1. Biên dịch — ĐẠT
Lệnh biên dịch:
```bash
g++ -std=c++17 -Wall -Wextra -O2 -Isrc -o phone_store src/main.cpp src/Phone.cpp src/Store.cpp src/Invoice.cpp src/utils.cpp
```
Kết quả: exit code 0, biên dịch thành công file thực thi `phone_store`.

## 2. Kiểm thử tự động (tests/test_store.cpp) — 24/24 PASS
Biên dịch `run_tests` từ `tests/test_store.cpp` + 4 file module và chạy `./run_tests` → exit code 0.
Kết quả 24 test case: PASS toàn bộ — add valid phone; duplicate id rejected; negative price rejected; negative stock rejected; empty id rejected; add second phone; findById found; findById not found; search by name; search by brand; search empty result; update phone; update missing rejected; create invoice; invoice total (= 44.000.000 cho 2 × 22.000.000); stock decreased (9 → 7); invoice over-stock rejected; stock unchanged after failed invoice; invoice empty lines rejected; revenue; save phones; load phones; remove phone; remove missing returns false.
Tổng kết: `Result: 24 passed, 0 failed`.

## 3. Kiểm thử chức năng qua Menu Console — ĐẠT
Kịch bản chạy thử: xem danh sách → tìm "Samsung" → thêm DT011 → xem lại → tạo hóa đơn → thống kê → xóa DT011 → thoát.
- Tải đúng **10 sản phẩm** từ `data/phones.txt`.
- Tìm "Samsung" trả về **2** máy (DT003, DT004).
- Thêm DT011 "Test Phone XYZ" thành công, danh sách lên 11 máy.
- Tạo hóa đơn **HD003**: Test Phone XYZ ×2 = **10.000.000 VND**.
- Thống kê: 3 hóa đơn, 6 máy đã bán, **tổng doanh thu 88.960.000 VND** (= 40.980.000 + 37.980.000 mẫu + 10.000.000 mới).
- Xóa DT011 có xác nhận → "Xoa thanh cong!"; thoát chương trình tự động lưu.

## 4. Kiểm tra ràng buộc và dữ liệu đầu vào
Trùng mã, giá âm, tồn âm, mã rỗng, sửa/xóa mã không tồn tại, bán quá tồn, hóa đơn rỗng — đều được chặn và thông báo lỗi rõ ràng. Nhập sai kiểu số ở menu được xử lý qua `readInt/readLongLong` trong `utils.cpp` (báo không hợp lệ, không gây treo vòng lặp).
