function imhist_expand(image)
    aux = zeros(size(image));
    channel = 'RGB';
    
    figure, subplot(2,4,1);
    imhist(rgb2gray(image));
    %axis([0 255 0 3e3]);
    title('Grayscale');
    grid on
    
    for i = 1:3,
        % Calculations
        [counts, binLoc] = imhist(image(:,:,i));
        
        rmin = find(counts>0, 1, 'first');
        rmax = find(counts>0, 1, 'last');
        
        aux(:,:,i) = round((double(image(:,:,i) - rmin)/double(rmax - rmin))*255.0);

        % Ploting
        subplot(2,4,i+1);
        imhist(image(:,:,i));
        %axis([0 255 0 1.5e3]);
        title(channel(i));
        grid on
        
        subplot(2,4,i+5);
        imhist(uint8(aux(:,:,i)));
        %axis([0 255 0 1.5e3]);
        title(channel(i));
        grid on
    end
    G = uint8(aux);
    
    subplot(2,4,5);
    imhist(rgb2gray(G));
    %axis([0 255 0 1.5e3]);
    title('Grayscale');
    grid on
    suptitle('Expansão de Histograma (histogramas)');
    
    pause;
    
    figure, imshowpair(image, G, 'montage');
    suptitle('Expansão de Histograma (comparação)');
end