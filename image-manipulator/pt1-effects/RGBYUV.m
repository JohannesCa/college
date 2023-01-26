function ret = RGBYUV(input)
    % Definin some constants
    Wr = 0.2126;
    Wb = 0.0722;
    Wg = 1 -Wr -Wb;
    Umax = 0.436;
    Vmax = 0.615;
    
    rgb = double(input);
    rgb = rgb./255; % Scaling input to [0, 1]
    s = size(input);
    yuv = double(zeros([s(1), s(2), 3]));
    
    for i = 1:s(1)
        for j = 1:s(2)
            % Converting color space
            yuv(i,j,1) = (Wr*rgb(i,j,1) + Wg*rgb(i,j,2) + Wb*rgb(i,j,3));
            yuv(i,j,2) = ((Umax/(1 - Wb))*(rgb(i,j,3) - yuv(i,j,1)));
            yuv(i,j,3) = ((Vmax/(1 - Wr))*(rgb(i,j,1) - yuv(i,j,1)));
            % Scaling output to [0, 255]
            yuv(i,j,1) = yuv(i,j,1)*(255);
            yuv(i,j,2) = (yuv(i,j,2)+(Umax))*255/(2*Umax);
            yuv(i,j,3) = (yuv(i,j,3)+(Vmax))*255/(2*Vmax);
        end
    end

    ret = uint8(round(yuv));
end