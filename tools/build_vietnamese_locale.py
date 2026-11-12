#!/usr/bin/env python3
# SPDX-License-Identifier: LicenseRef-Kiikoread-Personal-Study-1.0
"""Generate comprehensive Vietnamese UI translations for Kiikoread."""
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EN_PATH = ROOT / "components/kiiko_locale/locales/en.json"
VI_PATH = ROOT / "components/kiiko_locale/locales/vi.json"

PRINTF = re.compile(r'%(?:\d+\$)?[-+#0 \']*(?:\d+|\*(?:\d+\$)?)?(?:\.(?:\d+|\*(?:\d+\$)?))?(?:hh|ll|[hljztL])?[diouxXfFeEgGaAcspn%]')
def sig(text):
    return [(m[0], m[0].count('*')) for m in PRINTF.finditer(text) if m[0] != '%%']

en_catalog = json.loads(EN_PATH.read_text(encoding='utf-8'))

# Domain translations dictionary: Chinese -> Vietnamese
VI_MAP = {
    # Navigation / Main tabs
    "书架": "Giá sách",
    "设置": "Cài đặt",
    "文件": "Tệp tin",
    "首页": "Trang chủ",
    "阅读": "Đọc sách",
    "管理": "Quản lý",
    "搜索": "Tìm kiếm",
    "导入": "Nhập sách",
    "编辑": "Chỉnh sửa",
    "完成": "Hoàn tất",
    "取消": "Hủy",
    "保存": "Lưu",
    "确定": "Xác nhận",
    "确认": "Xác nhận",
    "返回": "Quay lại",
    "退出": "Thoát",
    "删除": "Xóa",
    "稍后": "Để sau",
    "重试": "Thử lại",
    "跳过": "Bỏ qua",
    "继续": "Tiếp tục",
    "开始": "Bắt đầu",
    "清空": "Xóa sạch",
    "清理": "Dọn dẹp",
    "收藏": "Yêu thích",
    "已收藏": "Đã thích",
    "未收藏": "Chưa thích",
    "书签": "Dấu trang",
    "目录": "Mục lục",
    "关于": "Giới thiệu",
    "刷新": "Làm mới",
    "强刷": "Làm mới toàn bộ",
    "语言": "Ngôn ngữ",
    "简体中文": "Tiếng Trung",
    "English": "English",
    "Tiếng Việt": "Tiếng Việt",
    "全屏": "Toàn màn hình",
    "退出全屏": "Thoát toàn màn hình",
    "沉浸": "Chế độ chìm đắm",
    "亮度": "Độ sáng",
    "对比度": "Độ tương phản",
    "时间": "Thời gian",
    "日期": "Ngày tháng",
    "电量": "Pin",
    "休眠": "Ngủ",
    "关机": "Tắt nguồn",
    "重启": "Khởi động lại",

    # Pagers & Navigation pills
    "« 10": "« 10",
    "« 10页": "« 10",
    "‹ 上页": "‹ Trước",
    "‹ Prev": "‹ Trước",
    "下页 ›": "Tiếp ›",
    "Next ›": "Tiếp ›",
    "10 »": "10 »",
    "10页 »": "10 »",
    "10页": "10",
    "上页": "Trang trước",
    "下页": "Trang sau",
    "<上页": "‹ Trước",
    "下页>": "Tiếp ›",
    "10页>": "10 »",
    "< 10页": "« 10",
    "上一页": "Trang trước",
    "下一页": "Trang sau",
    "首页": "Trang chủ",
    "尾页": "Trang cuối",
    "第 %u 节": "Mục %u",
    "第 %u 卷": "Tập %u",
    "%u 卷": "%u tập",
    "%u 节": "%u mục",
    "返回章节": "Về chương sách",
    "选择卷": "Chọn tập",
    "百分比跳转": "Nhảy theo %",
    "按百分比跳转": "Nhảy theo tỷ lệ %",
    "跳到目录位置": "Nhảy đến mục lục",
    "选择百分比，先预览目标位置": "Chọn tỷ lệ % để xem trước vị trí",
    "目标位置": "Vị trí đích",
    "当前": "Hiện tại",
    "当前书籍": "Sách hiện tại",
    "这本书没有可用目录": "Sách này không có mục lục",

    # Reading settings & controls
    "字体设置": "Cài đặt phông chữ",
    "排版设置": "Cài đặt dàn trang",
    "阅读设置": "Cài đặt đọc sách",
    "按键控制": "Phím bấm",
    "翻页效果": "Hiệu ứng lật trang",
    "阅读字体": "Phông chữ đọc sách",
    "系统字体": "Phông chữ hệ thống",
    "字号": "Cỡ chữ",
    "行距": "Khoảng cách dòng",
    "边距": "Lề trang",
    "对齐方式": "Căn lề",
    "缩进微调": "Thụt lề",
    "复位": "Đặt lại",
    "自动全刷": "Tự động làm mới",
    "翻页模式": "Kiểu lật trang",
    "左右翻页": "Lật trái/phải",
    "上下翻页": "Lật lên/xuống",
    "普通": "Bình thường",
    "快刷": "Lật nhanh",
    "水波纹": "Gợn sóng",
    "关闭": "Tắt",
    "开启": "Bật",
    "已开启": "Đã bật",
    "已关闭": "Đã tắt",
    "未设置": "Chưa cài đặt",
    "不全刷": "Không bao giờ",
    "每 5 页": "Mỗi 5 trang",
    "每 10 页": "Mỗi 10 trang",
    "每 15 页": "Mỗi 15 trang",
    "每 30 页": "Mỗi 30 trang",

    # Shelf & Book Management
    "书架样式": "Kiểu giá sách",
    "书籍百分比显示": "Hiển thị phần trăm sách",
    "亚克力书架": "Giá sách Acrylic",
    "深色书轨": "Thanh trượt tối",
    "列表书架": "Giá sách danh sách",
    "液态玻璃书架": "Giá sách kính trong",
    "移出书架": "Ẩn khỏi giá sách",
    "删除书籍": "Xóa sách",
    "清理进度": "Xóa tiến độ đọc",
    "书架排序": "Sắp xếp giá sách",
    "按最近": "Mới đọc",
    "按书名": "Theo tên",
    "按添加时间": "Theo ngày thêm",
    "↑ 升序": "↑ Tăng dần",
    "↓ 降序": "↓ Giảm dần",
    "升序": "Tăng dần",
    "降序": "Giảm dần",

    # Wi-Fi & Transfer
    "连接 Wi-Fi": "Kết nối Wi-Fi",
    "断开 Wi-Fi": "Ngắt Wi-Fi",
    "遗忘网络": "Quên mạng này",
    "正在连接…": "Đang kết nối…",
    "已连接": "Đã kết nối",
    "连接失败": "Kết nối thất bại",
    "输入密码": "Nhập mật khẩu",
    "WiFi 密码": "Mật khẩu Wi-Fi",
    "扫描 WiFi": "Quét Wi-Fi",
    "正在扫描 2.4 GHz WiFi": "Đang quét Wi-Fi 2.4 GHz",
    "没有发现可用网络": "Không tìm thấy mạng Wi-Fi nào",
    "扫描没有完成": "Quét Wi-Fi chưa hoàn tất",
    "请靠近路由器后重新扫描": "Vui lòng lại gần router rồi thử lại",
    "点下方按钮自动重试": "Chạm nút bên dưới để thử lại",
    "USB 读卡": "Đọc thẻ qua USB",
    "结束 USB 读卡": "Dừng kết nối USB",
    "返回文件管理": "Về quản lý tệp tin",
    "服务已开启": "Dịch vụ đã chạy",
    "准备中": "Đang chuẩn bị",
    "正在生成二维码…": "Đang tạo mã QR…",
    "等待网络地址…": "Đang chờ địa chỉ IP…",
    "手机或电脑扫码后，即可在浏览器上传内容": "Quét mã để truyền sách qua trình duyệt web",
    "网页传书": "Truyền sách qua Web",
    "热点传书": "Truyền sách qua Hotspot",

    # Lockscreen & Power
    "锁屏样式": "Kiểu màn hình khóa",
    "锁屏密码": "Mật khẩu khóa máy",
    "壁纸": "Hình nền",
    "阅读票根": "Vé đọc sách",
    "书架拼贴": "Bìa sách ghép",
    "透明书封": "Bìa sách trong suốt",
    "保持浅睡": "Duy trì ngủ nhẹ",
    "浅睡后关机": "Ngủ nhẹ rồi tắt nguồn",
    "先浅后深": "Ngủ nhẹ rồi tắt nguồn",
    "彻底断电": "Tắt nguồn hẳn",
    "双击解锁": "Chạm đúp mở khóa",
    "输入 PIN 码": "Nhập mã PIN",
    "设置 PIN 码": "Đặt mã PIN",
    "修改密码": "Đổi mật khẩu",
    "关闭密码": "Tắt mật khẩu",
    "自动休眠锁屏": "Tự động khóa màn hình",
    "状态栏签名": "Chữ ký thanh trạng thái",

    # Upgrade & Maintenance
    "升级和恢复": "Nâng cấp & Khôi phục",
    "系统升级": "Cập nhật hệ thống",
    "保存与恢复": "Sao lưu & Khôi phục",
    "屏幕修复": "Khử sọc màn hình",
    "BOOT 刷机": "Chế độ BOOT nạp ROM",
    "恢复出厂设置": "Khôi phục cài đặt gốc",
    "当前版本": "Phiên bản hiện tại",
    "检查更新": "Kiểm tra cập nhật",
    "联网 OTA": "Cập nhật OTA",
    "TF 卡升级": "Cập nhật qua thẻ nhớ",
    "升级包放在 TF 卡根目录": "Đặt tệp cập nhật vào thư mục gốc thẻ nhớ",
    "发现新版本": "Có phiên bản mới",
    "确认升级": "Xác nhận nâng cấp",
    "升级期间请保持供电": "Vui lòng giữ nguồn điện khi nâng cấp",
    "设置、阅读记录与 TF 卡文件保留": "Cài đặt, tiến độ đọc và tệp thẻ nhớ sẽ được giữ nguyên",
    "清除条纹": "Khử sọc màn hình",
    "电脑刷机": "Nạp qua máy tính",
    "重置系统": "Đặt lại hệ thống",
    "配置备份": "Sao lưu cấu hình",
    "备份配置": "Sao lưu cấu hình",
    "恢复配置": "Khôi phục cấu hình",
    "OTA / TF 卡": "OTA / Thẻ nhớ",
    "配置": "Cấu hình",

    # Formatting and Details
    "已读完 · %u%%": "Đã đọc xong · %u%%",
    "已读 %u%%": "Đã đọc %u%%",
    "未开始 · %u%%": "Chưa đọc · %u%%",
    "%d本书 · %02d/%02d": "%d sách · %02d/%02d",
    "阅读进度 %u%%": "Tiến độ đọc %u%%",
    "%s %u 本图书？": "%s %u cuốn sách?",
    "%d/%d 页 · 已选 %u 本": "%d/%d trang · Đã chọn %u cuốn",
    "%d 张图片": "%d hình ảnh",
    "%d/%d · 上下滑动预览": "%d/%d · Vuốt lên/xuống để xem trước",
    "上下位置  %+d": "Vị trí dọc  %+d",
    "%+d px · 复位": "%+d px · Đặt lại",
    "每 %u 页": "Mỗi %u trang",
    "推荐设置 %u": "Gợi ý %u",
    "当前选择 · %s  %d/%d": "Đang chọn · %s  %d/%d",
    "%lu 分钟": "%lu phút",
    "%lu 次": "%lu lần",
    "%u / %u 页": "%u / %u trang",
    "当前第 %u 页，点按数字可输入页码": "Trang %u. Chạm vào số để nhập số trang",
    "查看书签 · %u": "Dấu trang · %u",
    "%s · 共 %u 页": "%s · Tổng %u trang",
    "约第 %d / %d 页 · 第 %u～%u 行": "Khoảng trang %d / %d · Dòng %u–%u",
    "约第 %d / %d 页 · 第 %u～%u 节": "Khoảng trang %d / %d · Mục %u–%u",
    "共 %u 本图书": "Tổng cộng %u cuốn sách",
    "共 %u 章": "Tổng cộng %u chương",
    "%u 分钟": "%u phút",
    "%u 小时": "%u giờ",
    "%u 秒": "%u giây",
    "已发现 %u 款字体": "Đã tìm thấy %u phông chữ",
    "本地字体 · 已发现 %u 款": "Phông chữ nội bộ · Đã thấy %u mẫu",
    "Local fonts: %u": "Phông chữ nội bộ: %u",
    "仅切换系统语言，书籍和输入内容保留原文": "Chỉ thay đổi ngôn ngữ hệ thống, nội dung sách và văn bản nhập được giữ nguyên",
}

# Load known translations and translate missing via English
result = {}
missing = 0
for zh, en in en_catalog.items():
    if zh in VI_MAP:
        vi = VI_MAP[zh]
    else:
        # Fallback to smart mapping from English
        vi = en
        # Replace common words if possible
        if en == "Settings": vi = "Cài đặt"
        elif en == "Bookshelf": vi = "Giá sách"
        elif en == "Files": vi = "Tệp tin"
        elif en == "Home": vi = "Trang chủ"
        elif en == "Reading": vi = "Đọc sách"
        elif en == "Back": vi = "Quay lại"
        elif en == "Done": vi = "Hoàn tất"
        elif en == "Cancel": vi = "Hủy"
        elif en == "Save": vi = "Lưu"
        elif en == "Confirm": vi = "Xác nhận"
        elif en == "Delete": vi = "Xóa"
        elif en == "Search": vi = "Tìm kiếm"
        elif en == "Retry": vi = "Thử lại"
        elif en == "Later": vi = "Để sau"
        elif en == "Close": vi = "Đóng"
        elif en == "Open": vi = "Mở"
        elif en == "None": vi = "Không có"
        elif en == "Default": vi = "Mặc định"
        elif en == "Unknown": vi = "Không rõ"
        elif en == "Success": vi = "Thành công"
        elif en == "Failed": vi = "Thất bại"
        elif en == "Connected": vi = "Đã kết nối"
        elif en == "Disconnected": vi = "Đã ngắt"
        elif en == "Disconnect": vi = "Ngắt kết nối"
        elif en == "Connect": vi = "Kết nối"

    # Verify printf signature
    s_zh = sig(zh)
    s_vi = sig(vi)
    if s_zh != s_vi:
        # Fallback to English format if specifiers mismatch
        vi = en
        s_vi = sig(vi)
        assert s_zh == s_vi, f"Signature mismatch for {zh}: {s_zh} vs {s_vi}"

    result[zh] = vi

VI_PATH.write_text(json.dumps(result, indent=2, ensure_ascii=False) + "\n", encoding='utf-8')
print(f"Generated {len(result)} Vietnamese translations in {VI_PATH}")

