function emboss_filter(A, c)

if c == 1
    h = [ 0,        0,      0;
          0,        1,      0;
          0,        0,      -1];

elseif c == 2
    h = [ 0,        0,      -1;
          0,        1,      0;
          0,        0,      0 ];
      
elseif c == 3
    h = [ 0,        0,      2;
          0,        -1,     0;
          -1,       0,      0 ];
      
end

G = convolution(A, h);
figure, imshowpair(A, G, 'montage')

test = imfilter(A, h, 'conv');
figure, imshowpair(A, test,'montage')

end