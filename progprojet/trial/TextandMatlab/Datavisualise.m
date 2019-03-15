%%Text format%%
set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');
set(groot, 'defaultTextInterpreter', 'latex');
set(groot, 'defaultAxesFontSize', 18);

%%Analysis%%

%%Unpack Data%%
nsimul = 250;
%variable glossary:
%E = energy
%C = correlation
%A = total angle
%T = type
  %m_T = magnet type = ff,fw,ww
  %v_T = magnet types on a vertex (x3)
  %d_T = magnet types on a double vertex (x5)
  %f_T = magnet types on a face (x5)
%O = face orientation = 5,4,3,2


%system
load('data/evolve/angles'); %nx(T,E,C,ax30)
s = angles;
s_a = modpi(s(:,4:33));
%s_Aabs = sum(abs(s_a),);
s_A = sum(s_a);
s_E = s(:,2);
s_C = s(:,3); %maybe need a couple of different correlations
figure
histogram(s_E,10);
grid on
xlabel('energy');
title('E');
figure
histogram(s_C,10);
grid on
xlabel('correlation');
title('cor');
figure
hold on
scatter(s_C,s_E);
R = corrcoef(s_C,s_E);
grid on
xlabel('cor');
ylabel('E');

%magnets
load('data/evolve/magnets'); %nx30x(a,T)
m = reshape(magnets,[250,30,2]);
m_A = m(:,:,1);
m_T = m(:,:,2);

m_ff_A = zeros(250*30,2); %11411, 12411, 12421, (angle,type)
m_fw_A = zeros(size(m_A));
m_ww_A = zeros(size(m_A));
m_fff_A = zeros(size(m_A));

for i = 1:nsimul
  for j = 1:30
      ms = int16(mod(m_T(i,j),1000)/100) - 1;
      q = m_T(i,j);
    if ms == 3 %strong
      m_ff_A(i*j,1) = m_A(i,j);
      m_ff_A(i*j,2) = m_T(i,j);
    elseif ms == 2 %strong-weak 
      m_fw_A(i,j) =  m_A(i,j);
    elseif ms == 1 %strong-weak
      m_fw_A(i,j) = m_A(i,j);
    elseif ms == 0 %weak
      m_ww_A(i,j) = m_A(i,j);
      
    end
  end
end


m_ff_A = modpi(m_ff_A);
m_fw_A = modpi(m_fw_A);
m_ww_A = modpi(m_ww_A);

figure
histogram(m_ff_A,30);
grid on
xlabel('angle');
title('ff');
figure
histogram(m_fw_A,30);
grid on
xlabel('angle');
title('fw');
figure
histogram(m_ww_A,30);
grid on
xlabel('angle');
title('ww');

%% 

%vertices
v = load('data/vertices'); %shape:(nsimul)x(20)x(anglex3,typex3,E)
v_A = v(:,:,1:3);
v_T = v(:,:,4:6);
v_E = v(:,:,7);

%doublevertices
d = load('data/doublevertices'); %shape:(nsimul)x(30)x(anglex5,typex5,E)
d_A = d(:,:,1:5);
d_T = d(:,:,6:10);
d_E = d(:,:,11);

%faces
f = load('data/faces'); %shape:(nsimul)x(12)x(anglex5,Vtypex5,O,E)
f_A= f(:,:,1:5);
f_T = f(:,:,6:10);
f_E = f(:,:,11);
f_O = f(:,:,12);

%%%%%%% PLOTS %%%%%%%

%%scatter frequency plots%%
%s: all
%m: A, ff_A, fw_A, ww_A


%%histograms%%
%m_T
%v_T
%d_T
%f_T & f_T for each f_O

%%Gaussians (Box plots, show mean and std)%%
%T vs E for m,v,d,f

%%dependencies / correlations%%
%s: A, Aabs vs E
%s: A, Aabs vs C
%s: C vs E
%f_O vs f_E & f_O vs s_E

%think of good way to visualise frequency of face types, eg
%12 faces, each with one of four configs. Easiest is freq: number of perf faces


function y = modpi(x)
     x = x(x ~= 0);
    x = mod(x,pi);
    for i = 1:length(x)
    if x(i)>pi/2
        q = x(i);
        x(i) = pi - q;
    end
    end
    x = mod(x,pi);
    y = x;
end
