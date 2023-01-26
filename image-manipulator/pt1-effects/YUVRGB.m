function ret = YUVRGB(input)
    % Definin some constants
    Wr = 0.2126;
    Wb = 0.0722;
    Wg = 1 -Wr -Wb;
    Umax = 0.436;
    Vmax = 0.615;
    
    yuv = double(input);
    s = size(input);
    rgb = double(zeros([s(1), s(2), 3]));

    for i = 1:s(1)
        for j = 1:s(2)
            % Escaling input to [0, 1]
            yuv(i,j,1) = yuv(i,j,1)/(255.0);
            yuv(i,j,2) = ((yuv(i,j,2)/(255/2.0)) - 1)*Umax;
            yuv(i,j,3) = ((yuv(i,j,3)/(255/2.0)) - 1)*Vmax;
            % Converting color space
            rgb(i,j,1) = yuv(i,j,1) + yuv(i,j,3)*((1 - Wr)/Vmax);
            rgb(i,j,2) = yuv(i,j,1) - yuv(i,j,2)*((Wb*(1 - Wb))/(Umax*Wg)) - yuv(i,j,3)*((Wr*(1 - Wr))/(Vmax*Wg));
            rgb(i,j,3) = yuv(i,j,1) + yuv(i,j,2)*((1 - Wb)/Umax);
        end
    end

    ret = uint8(round(rgb.*255)); % Scaling output to [0, 255]
end