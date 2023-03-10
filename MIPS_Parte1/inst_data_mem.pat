
-- description generated by Pat driver

--			date     : Thu Nov 10 22:05:28 2016
--			revision : v109

--			sequence : inst_data_mem

-- input / output list :
in       clk B;;;
in       a (3 downto 0) B;;;
in       memwrite B;;;
in       wd B;;;
out      cod (31 downto 0) B;;;
out      funct (5 downto 0) B;;;
out      opcode (5 downto 0) B;;;
in       vdd B;;;
in       vss B;;;

begin

-- Pattern description :

--                          c  a     m  w   c                                  f        o       v  v   
--                          l        e  d   o                                  u        p       d  s   
--                          k        m      d                                  n        c       d  s   
--                                   w                                         c        o              
--                                   r                                         t        d              
--                                   i                                                  e              
--                                   t                                                                 
--                                   e                                                                 


-- Beware : unprocessed patterns

<          0 ps>Escrita_0 : 1  0000  0  0  ?00000000000000000000000000100000  ?100000  ?000000  1  0  ;
<          1 ps>Leitura_1 : 0  0001  0  0  ?00000000000000000000000000100010  ?100010  ?000000  1  0  ;
<          2 ps>Leitura_2 : 0  0010  0  0  ?00000000000000000000000000100100  ?100100  ?000000  1  0  ;
<          3 ps>Leitura_3 : 0  0011  0  0  ?00000000000000000000000000100101  ?100101  ?000000  1  0  ;
<          4 ps>Leitura_4 : 0  0100  0  0  ?00000000000000000000000000101010  ?101010  ?000000  1  0  ;
<          5 ps>Leitura_5 : 0  0101  0  0  ?00010000000000000000000000100000  ?100000  ?000100  1  0  ;
<          6 ps>Leitura_6 : 0  0110  0  0  ?00100000000000000000000000100000  ?100000  ?001000  1  0  ;
<          7 ps>Leitura_7 : 0  0111  0  0  ?00001000000000000000000000100000  ?100000  ?000010  1  0  ;

end;
