function gaussian_filter(A, N, sigma, op)
    h = make_mask(N, sigma, op);

    disp(h)
    G = convolution(A, h);
    figure, imshowpair(A, G, 'montage')

    test = fspecial('gaussian', [N N], sigma);
    Ig = imfilter(A, test, 'same');
    figure, imshowpair(A, Ig, 'montage')
end