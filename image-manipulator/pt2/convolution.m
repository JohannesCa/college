function ret = convolution(A, h)
    A = double(A);
    h = double(h);
    
    % Rebatimento
    hr = flip(fliplr(h));

    % Expansion by zeros
    newsize = size(hr);
    newsize = newsize(1:2);
    aux = size(A);
    aux = aux(1:2);
    newsize = (newsize -[1 1])*2 + aux;
    newsize = [newsize size(A, 3)];
    B = zeros(newsize);

    % Calculating temporary boundaries
    begin = size(hr);
    begin = begin(1:2);
    endin = aux + begin -[1 1];
    for k = 1:size(A, 3),
        B(begin(1):endin(1), begin(2):endin(2), k) = A(:,:,k);
    end
    G = zeros(endin(1), endin(2), size(A, 3));

    % Convolution loop
    for i = 1:endin(1),
        for j = 1:endin(2),
            temp = B(i:(begin(1)-1) +i, j:(begin(2)-1) +j, :);
            for k = 1:size(A, 3),
                G(i,j,k) = sum(sum(hr.*temp(:,:,k)));
            end
        end
    end
    
    % Cropping
    G = G(ceil(begin(1)/2):ceil(size(G,1)-(begin(1)/2)), ceil(begin(2)/2):ceil(size(G,2)-(begin(2)/2)), :);
    G = squeeze(G);
    
    ret = uint8(G);
end