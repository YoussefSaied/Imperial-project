% Ce script Matlab automatise la production de resultats
% lorsqu'on doit faire une serie de simulations en
% variant un des parametres d'entree.
%
% Il utilise les arguments du programme (voir ConfigFile.h)
% pour remplacer la valeur d'un parametre du fichier d'input
% par la valeur scannee.
%
% Note : pour relancer l'analyse des resultats sans relancer
% les simulations, utiliser "Run Section"
%
% LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libstdc++.so.6 matlab
%search run c++ in matlab
%
% Ce script Matlab automatise la production de resultats
% lorsqu'on doit faire une serie de simulations en
% variant un des parametres d'entree.
%
% Il utilise les arguments du programme (voir ConfigFile.h)
% pour remplacer la valeur d'un parametre du fichier d'input
% par la valeur scannee.
%
set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');
set(groot, 'defaultTextInterpreter', 'latex');
set(groot, 'defaultAxesFontSize', 18);

%% Parametres %%
repertoire = '';
executable = 'debug/simulationt';

input = 'configuration.in';


nsimul = 5;


% Indiquer ici les valeurs des parametres a scanner :
%dt = linspace(-4,-5,nsimul);
%dt= 0.01;
%dt = 10^-2 ./2.^linspace(1,nsimul,nsimul);
dt = logspace(-4,-6,nsimul);
%f = [2,2.25,2.5,2.6,2.7,2.8,2.9,3,3.25,3.5];%,20,50];
f = linspace(1,10,400);

% Selectionner ici le parametre a scanner
%paramstr = 'dt';
%param = dt;

paramstr = 'f';
param = f;
%time - correlation - sum angle - energy - kinetic
nsimul = length(param);

%% Simulations %%

output = cell(1, nsimul);


for i = 1:nsimul
    tic
    filename = [paramstr,'/',paramstr,'=', num2str(param(i))];
    output{i} = [filename];
    eval(sprintf('!%s %s %s=%.15g output=%s',executable, input, paramstr, param(i), output{i}));
    % Variante pour scanner Nx et Ny en meme temps:
    % eval(sprintf('!%s%s %s %s=%.15g %s=%.15g output=%s', repertoire, executable, input, [paramstr,'x'], param(i), [paramstr,'y'], param(i), output{i}));
    disp('Done.')
    toc
end

%% Analyse %%
%%%%%%%%%%%%%

if(strcmp(paramstr,'dt'))

%     t= zeros(200,1);
%     H= zeros(200,1);
%     for i = 1:nsimul
%     filename = [output{i}];
%     data = load([filename]);
%     t = [t ,data(:,1)];
%     H= [H,data(:,2)];
%     end
    t= zeros(199,1);
    angle= zeros(199,1);
    Energy = zeros(199,1);
    for i = 1:nsimul
    filename = [output{i}];
    data = load([filename]);
    t = [t ,data(:,1)];
    angle= [angle,data(:,2)];
    Energy= [Energy,data(:,3)];
    end
    t(:,1) = [];
    angle(:,1) = [];
    Energy(:,1) = [];

    filename = [output{nsimul}];
    data = load([filename]);

%     xmoyf_exact = data(end,6);
%     pmoyf_exact = data(end,8);
%     dxmoyf_exact = data(end,10);
%     dpmoyf_exact = data(end,11);

end

if(strcmp(paramstr,'f'))
    eqE = zeros(nsimul,1);
    eqtime = zeros(nsimul,1);
    eqCor = zeros(nsimul,1);
    
    for i = 1:length(f)
    %load
    filename = [output{i}];
    data = load([filename]);
    
    %unpack
    t = data(:,1);
    correlation = data(:,2);
    gradcor = gradient(correlation)
    angle = data(:,3);
    energy = data(:,4);
    kineticenergy = data(:,5);
    
    %figures per friction

%     figure
%     subplot(1,3,1)
%     plot(t,log(kineticenergy));
%     title(filename)
%     grid on
%     xlabel('time');
%     ylabel('KE')
%     subplot(1,3,2)
%     plot(t,correlation);
%     grid on
%     xlabel('time');
%     ylabel('corr');
%     subplot(1,3,3)
%     plot(t,log(abs(gradcor)));
%     grid on
%     xlabel('time');
%     ylabel('corr');
    
    %find eq
    for j = 1:length(kineticenergy)
    if kineticenergy(j) > 1e-10
        eqE(i) = energy(j);
        eqtime(i) = t(j);
        eqCor(i) = correlation(j);
    end
    end
    end

figure
plot(f,eqE);
grid on
xlabel('friction coef');
ylabel('KE');

figure
plot(f,eqtime);
grid on
xlabel('friction coef');
ylabel('eqtime')

figure
plot(f,eqCor);
grid on
xlabel('friction coef');
ylabel('correlation');
end




%% Figures

if(strcmp(paramstr,'dt'))
%convergence test:
figure
scatter(dt.^2,mod(angle(5,:),2*pi))
hold on
%plot([dt(1) dt(nsimul)].^2 ,[mod(angle(5,1),2*pi) mod(angle(5,nsimul),2*pi) ] )
grid on
xlabel('$dt^2$ [s]');
ylabel('$angle(100)$ [rad]');
% 
%cool plot:
figure
plot(t,mod(angle,2*pi))
grid on
xlabel('$t$ [s]');
ylabel('$angle$ [rad]');

%energy figure:
figure
plot(t,abs( Energy - Energy(1,:) ))
grid on
xlabel('$t$ [s]');
ylabel('$|E(t) - E(0)|$ [J]');

end

