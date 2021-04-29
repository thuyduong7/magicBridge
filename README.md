# Magic Bridge!
How to Play: Press left and right buttons to tilt the Magic Bridge! Try the best to avoid obstacles and collect coins. 
The number of enemies as well as their speed will be increased by each level.

Link demo: https://youtu.be/VzoHXJDiqLU

Mức điểm em nghĩ em xứng đáng đạt được: 9-10
Những công việc em đã làm:
  + Tự code hoàn chỉnh game:
      - Chia file dựa theo các chức năng của từng file:
        * Core chứa các hàm cơ bản cần có của game (init, load media, handle events, render,...)
        * Game chứa các hàm dùng để init cho mỗi lần chơi, handle events, render theo từng mode cụ thể (start, playing, help, settings, end) 
        * Materials dùng để chứa tất cả các ảnh, sprite cần cho game
        * Mỗi nhân vật, object có một file riêng để xử lý, các enemies kế thừa struct Enemy chính, coin cũng kế thừa Enemy (để dùng chung các hàm chính, còn đặc tính vẫn là tiền thưởng)
        * ...
     - Các tính năng: menu, settings (đổi background), quit, help, pause (bằng cách ấn settings hoặc help), replay, high score,...)
     - Di chuyển của nhân vật chính có quán tính (chạy thêm 1 đoạn dựa vào vận tốc ngay trước đó trước khi chuyển hướng), vận tốc xác định dựa theo độ nghiêng của cầu, thời gian chạy để chân thực hơn, có trạng thái nhấp nháy...
     - 4 loại quái với các cách xử lý khác nhau, cách di chuyển khác nhau
     - Loại tiền thưởng: coin (dùng để tính điểm)
     - Có level để xác định tốc độ, số lượng các quái
  + Thiết kế đồ họa bằng phần mềm GIMP (lấy ý tưởng từ game gốc):
     - Các nhân vật có sprite để chuyển động chân thực hơn
     - Background có 2 layers chuyển động với vận tốc khác nhau tăng tính chân thực cho game
     - 
