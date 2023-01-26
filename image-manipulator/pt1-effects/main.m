lena = imread('lena.bmp');
birds = imread('passaros.jpg');
desert = imread('deserto.jpg');
landscape = imread('paisagem.jpg');
beans = imread('feijao.jpg');
castle = imread('castelo.jpg');
fruits = imread('fruit.jpg');

yuvfruits = RGBYUV(fruits);

figure, imshowpair(fruits,yuvfruits,'montage');
pause;


rgb_components(lena);
pause;


rgb_components(birds);
pause;


negative_effect(lena, false);
pause;
negative_effect(birds, false);
pause;


negative_effect(lena, true);
pause;
negative_effect(birds, true);
pause;


brightness_effect(lena, 50, 1, false);
pause;
brightness_effect(lena, 50, 1, true);
pause;
brightness_effect(lena, 5, 2, false);
pause;
brightness_effect(lena, 5, 2, true);
pause;


brightness_effect(birds, 50, 1, false);
pause;
brightness_effect(birds, 50, 1, true);
pause;
brightness_effect(birds, 5, 2, false);
pause;
brightness_effect(birds, 5, 2, true);
pause;


noise_average_median(false);
pause;
noise_average_median(true);
pause;


contrast_effect(beans);
pause;


add_effect(desert, landscape);
pause;


smoothing_effect(castle, 1);
pause;
smoothing_effect(castle, 2);
pause;