# 1. Quản Lý Cửa Hàng Bán Điện Thoại — Phone Store Management

## 2. Môn học tương ứng
**Nhập môn lập trình** — Nhóm 1, Đồ án CNTT. Ngôn ngữ: C++17.

## 3. Giới thiệu đề tài
Chương trình console quản lý cửa hàng điện thoại: quản lý sản phẩm, tồn kho, bán hàng qua hóa đơn và thống kê doanh thu. Dữ liệu lưu bền vững trong file văn bản định dạng CSV-like (`data/phones.txt`, `data/invoices.txt`) nên đóng/mở lại chương trình không mất dữ liệu.

## 4. Mục tiêu thực hiện
- Vận dụng `struct/class`, `vector`, hàm, tách module trong C++.
- Thực hành CRUD, tìm kiếm, kiểm tra dữ liệu đầu vào và xử lý lỗi.
- Thực hành đọc/ghi file, tính toán hóa đơn và thống kê.
- Tổ chức mã nguồn theo module dễ đọc, dễ bảo trì, có kiểm thử tự động.

## 5. Công nghệ sử dụng
| Thành phần | Công nghệ |
|---|---|
| Ngôn ngữ | C++17 |
| Trình biên dịch | g++ 11+ (hoặc trình biên dịch hỗ trợ C++17), CMake ≥ 3.16 (tùy chọn) |
| Lưu trữ | File text CSV-like, không cần cài database |
| Kiểm thử | Chương trình test tự viết (`tests/test_store.cpp`), assert qua macro CHECK |
| Giao diện | Console (terminal) |

## 6. Danh sách chức năng
1. Xem danh sách điện thoại (mã, tên, hãng, giá, tồn kho).
2. Thêm điện thoại — chống trùng mã, chống giá âm / tồn âm / trường rỗng.
3. Sửa điện thoại theo mã.
4. Xóa điện thoại — có bước xác nhận `y/n`.
5. Tìm kiếm theo tên, mã hoặc hãng (không phân biệt hoa/thường).
6. Quản lý tồn kho — tồn tự giảm khi bán, không cho bán quá tồn.
7. Tạo hóa đơn bán hàng nhiều dòng — kiểm tra toàn bộ trước khi trừ kho (atomic: một dòng lỗi thì không trừ kho dòng nào), tính tổng tiền.
8. Thống kê: tổng số hóa đơn, tổng máy đã bán, tổng doanh thu, tổng giá trị tồn kho.
9. Lưu / tải lại dữ liệu từ file.
10. Kiểm tra dữ liệu đầu vào: nhập sai kiểu số được báo lỗi, không crash.

## 7. Kiến trúc và cấu trúc thư mục
Kiến trúc 3 lớp đơn giản: `main.cpp` (giao diện menu) → `Store` (nghiệp vụ) → `Phone`/`Invoice` (dữ liệu) + `utils` (tiện ích dùng chung).

```
QL_CHDT/
├── src/
│   ├── main.cpp      # Menu console, điều phối
│   ├── Phone.h/.cpp  # Lớp điện thoại, validate, CSV
│   ├── Store.h/.cpp  # CRUD, tìm kiếm, hóa đơn, thống kê, file I/O
│   ├── Invoice.h/.cpp# Lớp hóa đơn và dòng hóa đơn
│   └── utils.h/.cpp  # trim, split CSV, format tiền, nhập số an toàn
├── data/
│   ├── phones.txt    # 10 điện thoại mẫu
│   └── invoices.txt  # 2 hóa đơn mẫu
├── tests/
│   └── test_store.cpp# 24 test case tự động
├── docs/
│   ├── TEST_REPORT.md
│   └── HUONG_DAN.md
├── assets/           # (trống — dự án console, giữ chỗ cho ảnh chụp)
├── Makefile
├── CMakeLists.txt
├── .gitignore
├── LICENSE           # MIT
└── README.md
```

## 8. Hình ảnh giao diện (screenshots)
Dự án là ứng dụng console — mô tả ảnh chụp dự kiến:
- `assets/menu.png` *(placeholder)*: menu chính 0–9 sau khi tải 10 sản phẩm.
- `assets/list.png` *(placeholder)*: bảng danh sách 10 điện thoại với giá định dạng `29.990.000 VND`.
- `assets/invoice.png` *(placeholder)*: hóa đơn HD003 — Test Phone XYZ ×2 = 10.000.000 VND và màn thống kê doanh thu 88.960.000 VND.
> Cách tự chụp: chạy chương trình theo mục 10, chụp terminal ở từng màn hình và lưu vào `assets/` với đúng tên trên.

## 9. Hướng dẫn cài đặt môi trường
- **Linux/Ubuntu:** `sudo apt install g++ make cmake`
- **Windows:** cài MinGW-w64 (g++) hoặc Visual Studio có workload C++, chạy trong terminal tại thư mục dự án.
- **macOS:** `xcode-select --install`
- Kiểm tra: `g++ --version`

## 10. Hướng dẫn chạy chương trình
```bash
cd QL_CHDT
# Cách 1 — g++ trực tiếp
g++ -std=c++17 -Wall -Wextra -O2 -Isrc -o phone_store src/main.cpp src/Phone.cpp src/Store.cpp src/Invoice.cpp src/utils.cpp
./phone_store
# Cách 2 — Make
make && ./phone_store
# Cách 3 — CMake
cmake -S . -B build && cmake --build build && ./build/phone_store
```
⚠️ Phải chạy từ thư mục gốc dự án vì chương trình đọc `data/phones.txt` theo đường dẫn tương đối.

**Chạy kiểm thử:**
```bash
make test        # hoặc: g++ -std=c++17 -Isrc -o run_tests tests/test_store.cpp src/Phone.cpp src/Store.cpp src/Invoice.cpp src/utils.cpp && ./run_tests
```

## 11. Tài khoản demo
Không có đăng nhập. Dữ liệu demo có sẵn: 10 điện thoại (DT001–DT010) và 2 hóa đơn (HD001, HD002). Thao tác thử nhanh: chọn `1` xem danh sách → `5` tìm `Samsung` → `6` tạo hóa đơn mua DT011/DT001 → `7` xem doanh thu → `0` thoát (tự lưu).

## 12. Hướng phát triển trong tương lai
- Thêm quản lý khách hàng và nhà cung cấp / phiếu nhập kho.
- Lọc theo khoảng giá, sắp xếp theo giá/tồn kho.
- Xuất hóa đơn ra file text/PDF, báo cáo doanh thu theo ngày/tháng.
- Chuyển lưu trữ sang SQLite, thêm giao diện đồ họa (Qt).
- Thêm mã vạch / tìm kiếm gần đúng.

---
*Giấy phép: MIT — xem file `LICENSE`.*
