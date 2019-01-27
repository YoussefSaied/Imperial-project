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
repertoire = './';
executable = 'simulationt';

input = 'configuration.in';


nsimul = 20;


% Indiquer ici les valeurs des parametres a scanner :
dt = logspace(-1,-2,nsimul);
f = linspace(0,100,nsimul);


% Selectionner ici le parametre a scanner
 paramstr = 'dt';
 param = dt;

 %paramstr = 'f';
 %param = f;


%% Simulations %%

output = cell(1, nsimul);

tic
for i = 1:nsimul
    tic
    filename = [paramstr, '=', num2str(param(i))];
    output{i} = [filename];
    eval(sprintf('!%s%s %s %s=%.15g output=%s', repertoire, executable, input, paramstr, param(i), output{i}));
    % Variante pour scanner Nx et Ny en meme temps:
    % eval(sprintf('!%s%s %s %s=%.15g %s=%.15g output=%s', repertoire, executable, input, [paramstr,'x'], param(i), [paramstr,'y'], param(i), output{i}));
    disp('Done.')
    toc
end
toc

%% Analyse %%
%%%%%%%%%%%%%

if(strcmp(paramstr,'dt'))

    t= zeros(200,1);
    H= zeros(200,1);
    for i = 1:nsimul
    filename = [output{i}];
    data = load([filename]);
    t = [t ,data(:,1)];
    H= [H,data(:,2)];
    end


    filename = [output{nsimul}];
    data = load([filename]);

%     xmoyf_exact = data(end,6);
%     pmoyf_exact = data(end,8);
%     dxmoyf_exact = data(end,10);
%     dpmoyf_exact = data(end,11);

end

if(strcmp(paramstr,'f'))
     xmoyf = zeros(1,nsimul);
     P1 = zeros(1501,nsimul); %1501 pour 150s et dt=0.1
     P2 = zeros(1501,nsimul);
     P3 = zeros(1501,nsimul);

    for i = 1:nsimul
    filename = [output{i}];
    data = load([filename,'_obs.out']);
    t = data(:,1);
    P1(:,i) = data(:,2);
    P2(:,i) = data(:,3);
    P3(:,i) = data(:,4);
    end
end




%% Figures

if(strcmp(paramstr,'dt'))

figure
plot(t,H)
grid on
xlabel('$t$ [s]');
ylabel('$H$ [J]');


end


if(strcmp(paramstr,'f'))
    figure
    plot(t,P1);
    grid on
    xlabel('Time t [s]');
    ylabel('$P_{x<x_a}(t)$ [ ]')
    legend('$V_0 = 0.8E$','$V_0 = E$','$V_0 = 1.1 E$')

    figure
    plot(t,P2);
    grid on
    xlabel('Time t [s]');
    ylabel('$P_{x_a \le x \le x_b}(t)$ [ ]')
    legend('$V_0 = 0.8E$','$V_0 = E$','$V_0 = 1.1 E$')

    figure
    plot(t,P3);
    grid on
    xlabel('Time t [s]');
    ylabel('$P_{x>x_b}(t)$ [ ]')
    legend('$V_0 = 0.8E$','$V_0 = E$','$V_0 = 1.1 E$')

    figure
    plot(V0/0.3081,P3(end,:),'+')
    hold on
    line([1 1], [0.1 0.8]);
    line([0.7 1.2], [0.5 0.5]);
    line([0.832382 0.832382], [0.1 0.8]);
    pV0 = polyfit(V0/0.3081,P3(end,:),1)
    pvV0 = polyval(pV0,V0/0.3081);
    plot(V0/0.3081,pvV0,'--')
    xlabel('$V0/E$ [ ]')
    ylabel('$P_{x>x_b}(t)$ [ ]')

end
