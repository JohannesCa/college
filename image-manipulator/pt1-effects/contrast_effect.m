function contrast_effect(img)

contr = imadjust(img,[.2 .3 0; .6 .7 1],[]);
figure
imshowpair(img,contr,'montage')
imwrite(contr,'contrast.jpg')

end