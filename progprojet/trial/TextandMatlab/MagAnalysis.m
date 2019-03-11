%%Text format%%
set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');
set(groot, 'defaultTextInterpreter', 'latex');
set(groot, 'defaultAxesFontSize', 18);

%%Unpack Data%%

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
s = load('data/system');
s_Aabs = sum(abs(s(:,:,1:30)))
s_A = sum(s(:,:,1:30))
s_E = s(:,;,31);
s_C = s(:,:,32); %maybe need a couple of different correlations

%magnets
m = load('data/magnets'); %shape:(nsimul)x(30)x(angle,type)
nsimul = length(m(:,,1,1));
m_A = m(:,:,1);
m_T = m(:,:,2);

m_ff_A = [];
m_fw_A = [];
m_ww_A = [];

for i in 1:nsimul
  for j in 1:30
    if m_T(i,j) == 3 %strong
      m_ff_A = [m_ff_A,m_A(i,j)]
      end
    elseif m_T(i,j) == 2 %strong-weak
      m_fw_A = [m_fw_A,m_A(i,j)]
      end
    elseif m_T(i,j) == 1 %strong-weak
      m_fw_A = [m_fw_A,m_A(i,j)]
      end
    elseif m_T(i,j) == 0 %weak
      m_ww_A = [m_ww_A,m_A(i,j)]
      end
  end
end

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
