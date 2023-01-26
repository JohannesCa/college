function sharpness_filter(A, C, D, a)

if a == 1
    h = [ 0,     -C,     0;
         -C,    4*C+D,   0;
          0,     -C,     0];

elseif a == 2
    h = [-C,    -C,     -C;
         -C,   8*C+D,   -C;
         -C,    -C,     -C];
end

G = convolution(A, h);
figure, imshowpair(A, G, 'montage')

test = imfilter(A, h, 'conv');
figure, imshowpair(A, test,'montage')

end