function negative_effect(img, yuvop)

if yuvop == true
    negative = RGBYUV(img);
    negative(:,:,1) = uint8(-1*(double(negative(:,:,1)-255)));
    negative = YUVRGB(negative);
    imshowpair(img,negative,'montage')
    imwrite(negative,'negative2.bmp')
else
    negative = uint8(-1*(double(img)-255));
    imshowpair(img,negative,'montage')
    imwrite(negative,'negative1.bmp')
end
end