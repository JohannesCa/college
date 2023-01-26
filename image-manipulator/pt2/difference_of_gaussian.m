function ret = difference_of_gaussian(A, N, sigma1, sigma2)    
    % Funções implementadas
    gauss1 = make_mask(N, sigma1, 1);
    gauss2 = make_mask(N, sigma2, 1);
    blur1 = convolution(A, gauss1);
    blur2 = convolution(A, gauss2);
    
    dog = blur1 - blur2;
    figure, imshowpair(A, dog,'montage');

    % Funções do MATLAB
    gauss1 = fspecial('gaussian', round([N*sigma1 N*sigma1]), sigma1);
    gauss2 = fspecial('gaussian', round([N*sigma2 N*sigma2]), sigma2);
    
    blur1 = imfilter(A, gauss1, 'replicate', 'same');
    blur2 = imfilter(A, gauss2, 'replicate', 'same');

    dog = blur1 - blur2;
    %figure, imshowpair(A, dog,'montage')
    
    ret = dog2;
end
