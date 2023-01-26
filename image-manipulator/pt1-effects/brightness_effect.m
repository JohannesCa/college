function brightness_effect(img, bright, op, yuvop)

% Additive
if op == 1
    if yuvop == true
        brighter = RGBYUV(img);
        brighter(:,:,1) = imadd(brighter(:,:,1), bright);
        brighter = YUVRGB(brighter);
    else
        brighter = imadd(img, bright);
    end
    imshowpair(img,brighter,'montage')
    imwrite(brighter,'brighter1.jpg')
% Multiplicative
elseif op == 2
    if yuvop == true
        brighter = RGBYUV(img);
        brighter(:,:,1) = immultiply(brighter(:,:,1), bright);
        brighter = YUVRGB(brighter);
    else
        brighter = immultiply(img, bright);
    end
        imshowpair(img,brighter,'montage')
        imwrite(brighter,'brighter2.jpg')
end