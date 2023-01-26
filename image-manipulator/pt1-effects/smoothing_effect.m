function smoothing_effect(img, op)

noi = imnoise(img,'salt & pepper',0.01);
% Avarage
if op == 1
    H = fspecial('average',[3 3]);
    smoothed = imfilter(noi,H,'replicate');

    imshowpair(noi,smoothed,'montage')
    imwrite(noi,'noised.jpg')
    imwrite(smoothed,'smoothed.jpg')

% Median
elseif op == 2
    R = noi(:,:,1);
    G = noi(:,:,2);
    B = noi(:,:,3);

    smoothed(:,:,1) = medfilt2(R);
    smoothed(:,:,2) = medfilt2(G);
    smoothed(:,:,3) = medfilt2(B);

    imshowpair(noi,smoothed,'montage')
    imwrite(noi,'noised2.jpg')
    imwrite(smoothed,'smoothed2.jpg')
end
end