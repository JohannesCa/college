function add_effect(img1, img2)

img3 = (img1 + img2)/2;
figure
subplot(2,2,1); imshow(img1); title('Deserto')
subplot(2,2,2); imshow(img2); title('Paisagem')
subplot(2,2,3); imshow(img3); title('Deserto + Paisagem')

imwrite(img3,'added.jpg')
end