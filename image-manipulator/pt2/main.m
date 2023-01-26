clear

butterfly = imread('monarch_in_may.jpg');
castle = imread('castelo.jpg');
lena = imread('lena_mono.jpg');
boat = imread('boat.jpg');

%h = [-1 -1 -1; 0 0 0; 1 1 1];
%h = [-1 -1 -1; -1 8 -1; -1 -1 -1];
%h = repmat(1/9, 3);
%h = [0.025 0.1 0.25; 0.1 0.5 0.1; 0.025 0.1 0.025];
%h = normrnd(-0.7,0.35,3,3)
vibesmask


%% -------- CONVOLU��O --------------------------------
%{
G = convolution(butterfly, h);
test = imfilter(butterfly, h, 'conv');

figure, subplot(2,1,1);
imshowpair(butterfly, G, 'montage')
title('Pr�pria')

subplot(2,1,2);
imshowpair(butterfly, test,'montage')
title('Matlab')
suptitle('Convolu��o com h')

%
test2 = rgb2gray(butterfly);
G = convolution(test2, h);
figure, imshowpair(test2, G, 'montage');
%}

%% -------- AGU�AMENTO --------------------------------
%{
a = 2;     % mask type
C = 1;
D = 1;
sharpness_filter(butterfly, C, D, a);      % agu�amento a = 1,2
%}

%% -------- DETEC��O DE BORDAS ------------------------
%{
b = 4;     % mask type
edge_detection_filter(castle, b);      % detec��o b = 1,2,3,4
%}

%% -------- RELEVO ------------------------------------
%{
c = 1;     % mask type
emboss_filter(castle, c);      % relevo c = 1,2,3
%}

%% -------- GAUSSIANO ---------------------------------
%{
N = 5;      % Size of Gaussian mask
sigma = 2;
gaussian_filter(castle, N, sigma, 2);    
%}

%% -------- M�DIA MxN ---------------------------------
%{
M = 5;
N = 5;
averageMxN(castle, M, N);
%}

%% -------- COMPARA��ES POR M�DIA  --------------------
%{
M = 5;
N = 5;
result = average_comparisons(castle, M, N);

M = 10;
N = 1;
average_comparisons(result, M, N);
%}

%% -------- MEDIAN ------------------------------------
%{
mask_size = 3;    % median (3,5,...)
median_filter(lena, mask_size);
%}

%% -------- Difference of Gaussian --------------------
%{
N = 5; 
sigma1 = 0.5;
sigma2 = 1;
difference_of_gaussian(butterfly, N, sigma1, sigma2);
%}

%% -------- EXPANS�O DE HISTOGRAMA --------------------

%imhist_expand(boat);


%% -------- EQUALIZA��O DE HISTOGRAMA -----------------

%imhist_equalize(boat);