function rgb_components(img_name)

%disp(img_name);
red = uint8(zeros(size(img_name)));
green = uint8(zeros(size(img_name)));
blue = uint8(zeros(size(img_name)));

red(:,:,1) = img_name(:,:,1);
green(:,:,2) = img_name(:,:,2);
blue(:,:,3) = img_name(:,:,3);

figure
subplot(2,2,1); imshow(img_name); title('Imagem colorida')
subplot(2,2,2); imshow(red); title('Componentes de vermelho - R')
subplot(2,2,3); imshow(green); title('Componentes de verde - G')
subplot(2,2,4); imshow(blue); title('Componentes de azul - B')

imwrite(red,'red.bmp')
imwrite(green,'green.bmp')
imwrite(blue,'blue.bmp')

end