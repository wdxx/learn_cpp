/// 最终版本  参考 art/runtime/gc/space/image_space.h 中LoadBootImage 方法的注释
oatdump --boot-image=/system/framework/boot.art:/system/framework/boot-framework.art --app-image=/data/app/~~tQprJ1_rkYYE0YrVLGVqJw==/com.UCMobile-4oPXPvB0D7ZRac66jgA4bw==/oat/arm64/base.art --oat-file=/data/app/~~tQprJ1_rkYYE0YrVLGVqJw==/com.UCMobile-4oPXPvB0D7ZRac66jgA4bw==/oat/arm64/base.odex

//// 可用导出 app.art
oatdump --image=/system/framework/boot.art:/system/framework/boot-framework.art --app-image=/data/app/~~tQprJ1_rkYYE0YrVLGVqJw==/com.UCMobile-4oPXPvB0D7ZRac66jgA4bw==/oat/arm64/base.art --app-oat=/data/app/~~tQprJ1_rkYYE0YrVLGVqJw==/com.UCMobile-4oPXPvB0D7ZRac66jgA4bw==/oat/arm64/base.odex


oatdump --image=/system/framework/boot.art:/system/framework/boot-framework.art --app-image=/data/app/~~IMO-w9fgjXObiHu6K5-0Ig==/com.example.testoat-t9QKtWJq1UrYDXjPaRSFxw==/oat/arm64/base.art --app-oat=/data/app/~~IMO-w9fgjXObiHu6K5-0Ig==/com.example.testoat-t9QKtWJq1UrYDXjPaRSFxw==/oat/arm64/base.odex

oatdump --oat-file=base.odex --class-filter=com.example.A.CCC --method-filter=run
