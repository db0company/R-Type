%******************************************************************************%
%                                                                              %
%                           koala.cls                                          %
%                           Made by:                                           %
%                                Maxime MONTINET                               %
%                                David GIRON                                   %
%                                Uriel `korfuri' CORFA <korfuri@korfuri.fr>    %
%                                François PRADEL                               %
%                                                                              %
%******************************************************************************%

%
% This class provides a layout for teaching material in Epitech.
% It includes various features for both the Koalab and the LabAstek.
%
% This is version 2 of this class.
%
% This class is organized this way :
%
% I - General LaTeX boilerplate
%  1. Definition
%  2. Imports
%  3. Class options
% II - Lengths and color redefinitions
%  1. Lenghts
%  2. Colors
%  3. Hyperlinks
%  4. Listings
%  5. Page layout
%  6. Roman numerals for chapters
% III - Frontpage customization
%  1. Custom fields
%  2. Redefinition of \maketitle
% IV - Custom helper commands
%  1. Hint/warn
%  2. Lisibility helper
% VII - Custom tables for C++ subjects
%  1 - Custom tables for piscine



%%
%% I - General LaTeX boilerplate
%%

%% I.1 - Definition

\NeedsTeXFormat{LaTeX2e}[1995/12/01]
\ProvidesClass{koala}[2010/07/15 v2.0
  LaTeX class for Koala-themed documents]

\LoadClass[a4paper,12pt,onecolumn]{report}

%% I.2 - Imports

\usepackage[top=1in,bottom=1in,left=1in,right=1in]{geometry}
\usepackage[pdftex]{graphicx}
\usepackage{url}
\usepackage{fancyhdr}
\usepackage{array}
\usepackage[table]{xcolor}
\usepackage[utf8]{inputenc}
\usepackage[T1]{fontenc}
\usepackage{lmodern}
\usepackage{listings}
\usepackage{tabularx}
\usepackage{color}
\usepackage[pdftex]{hyperref}
\usepackage{fancybox}
\usepackage{float}
\usepackage{atbeginend} % provided locally : atbeginend.sty
\usepackage{tocloft} % provided locally : tocloft.sty
\usepackage{multirow} % provided locally : multirow.sty

%% I.3 - Class options

\newcommand{\summarytitle}{Abstract}
\DeclareOption{fr}{%
  \renewcommand{\summarytitle}{Abstract}
}

\DeclareOption*{%
  \PassOptionsToClass{\CurrentOption}{report}
}
\ProcessOptions\relax

%% II - Lengths and color redefinitions

%% II.1 - Lengths

\AfterBegin{enumerate}{
  \itemsep10pt%
}
\AfterBegin{itemize}{
  \itemsep10pt%
  \renewcommand{\labelitemi}{$\bullet$}%
  \renewcommand{\labelitemii}{$\circ$}%
}

\BeforeBegin{enumerate}{\vspace{15pt}}
\AfterEnd{enumerate}{\vspace{15pt}}

\BeforeBegin{itemize}{\vspace{15pt}}
\AfterEnd{itemize}{\vspace{15pt}}

\BeforeBegin{lstlisting}{\vspace{15pt}}
\AfterEnd{lstlisting}{\vspace{15pt}}

\BeforeBegin{tabularx}{\vspace{15pt}}
\AfterEnd{tabularx}{\vspace{15pt}}

%% II.2 - Colors

\definecolor{nicergreen}{rgb}{0,0.502,0}
\definecolor{nicerblue}{rgb}{0,0.302,1}
\definecolor{nicerorange}{rgb}{1,0.502,0}
\definecolor{nicergrey}{rgb}{0.502,0.502,0.502}
\definecolor{nicerred}{rgb}{0.626,0,0}
\definecolor{hintbg}{rgb}{1.0,1.0,0.75}
\definecolor{warnbg}{rgb}{1.0,0.75,0.75}
\definecolor{infobg}{rgb}{0.75,0.75,1.0}

%% II.3 - Hyperlinks

\hypersetup
{
  colorlinks,
%  citecolor=black,                %
%  filecolor=black,                %
  linkcolor=black,                % black links
  urlcolor=blue                   % blue URLs
}

%% II.4 - Listings

\lstset
{
  backgroundcolor=\color{gray!15},
  basicstyle=\small\ttfamily,
  breaklines=true,
  columns=fullflexible,
  frame=lines,
  tabsize=4,
  numbers=left,
  numberstyle=\scriptsize\ttfamily,
  numbersep=5pt,
  showspaces=false,
  showstringspaces=false,
  showtabs=false,
  breaklines=true,
  float
}

%% II.5 - Page layout

\makeatletter
\pagestyle{fancy}
\lhead{\@title}
\rhead{\@subtitle}
\cfoot{\thepage}
\makeatother

%% II.6 - Roman chapter style

% custom sections style

\renewcommand{\thechapter}{\Roman{chapter}}

% Using  roman  numerals  makes  the  TOC  section/subsection  numbers
% overflow on the  right. This adds some margin to  avoid that kind of
% problems. (requires \usepackage{tocloft})
\setlength{\cftchapnumwidth}{1cm}
\setlength{\cftsecnumwidth}{1cm}
\setlength{\cftsubsecnumwidth}{1.3cm}
\setlength{\cftsubsubsecnumwidth}{1.6cm}


%% III - Frontpage customization

%% III.1 - Custom fields
\makeatletter
\newcommand{\website}[1]{\def \@website {#1}}
\website{}

\newcommand{\subtitle}[1]{\def \@subtitle {#1}}
\subtitle{}

\newcommand{\koalalogo}[1]{\def \@koalalogo {#1}}
\koalalogo{rtype_logo.png}

%%\newcommand{\schoollogo}[1]{\def \@schoollogo {#1}}
%%\schoollogo{epitech_logo.pdf}

\newcommand{\summary}[1]{\def \@summary {#1}}
\summary{}

\edef\@authors{}
\newcommand{\member}[2]{%
  \protected@edef\@authors{\@authors #1 \protect\url{#2}\\}
  \author{\@authors}
}
\author{}

%% III.2 - Redefine \maketitle

\makeatletter
\def \maketitle {
  \begin{titlepage}
    \begin{center}

	\begin{figure}[t]
	\begin{minipage}[m]{0.5\linewidth}
	\includegraphics[width=16cm]{\@koalalogo}
	\end{minipage}
	\end{figure}
      \vskip 3em
      {\huge \@title}
      \vskip 2em
      {\LARGE \@subtitle}
      \vskip 5em
    \end{center}
    \begin{center}
	  \@author
    \end{center}
	\vskip 3em
    \emph{\summarytitle : \@summary}
  \end{titlepage}
}
\makeatother

\fancyput(-2.54cm,-27.16cm){\includegraphics[width=21cm,height=29.7cm]{back.png}}

%% IV - Custom helper commands

%% IV.1 - Hint/Warn

% hint command

\newcommand{\kbox}[3]
{
  \vskip 15pt
  \noindent
  \colorbox{#1}
  {
    \begin{tabular*}{\textwidth}{m{4em}m{0.8\textwidth}}
        \includegraphics[width=4em]{#2}
      & {\ttfamily\footnotesize #3}\\
    \end{tabular*}
  }
  \vskip 15pt
}

\newcommand{\hint}[1]{\kbox{hintbg}{helphint.pdf}{#1}}
\newcommand{\warn}[1]{\kbox{warnbg}{warn.pdf}{#1}}
\newcommand{\info}[1]{\kbox{infobg}{info.pdf}{#1}}

%% VI.2 Lisibility helper

\makeatletter
\newcommand{\mso}[1]{
  \ttfamily #1 \normalfont
}

%% VII - Custom tables for C++ subjects

%% VII.1 - Custom fields for tables

\makeatletter
\newcommand{\turnindir}[1]{\def \@turnindir {#1}}

\newcommand{\daypiscine}[1]{\def \@daypiscine {#1}}

\newcommand{\extitle}[1]{\def \@extitle {#1}}

\newcommand{\exnumber}[1]{\def \@exnumber {#1}}

\newcommand{\exscore}[1]{\def \@exscore {#1}}

\newcommand{\exflags}[1][-W -Wall -Werror]{\def \@exflags {#1}}

\newcommand{\excompil}[1][g++]{\def \@excompil {#1}}

\newcommand{\exmake}[1][Non]{\def \@exmake {#1}}

\newcommand{\exrules}[1][n/a]{\def \@exrules {#1}}

\newcommand{\exfiles}[1]{\def \@exfiles {#1}}

\newcommand{\exnotes}[1][n/a]{\def \@exnotes {#1}}

\newcommand{\exforbidden}[1][Aucune]{\def \@exforbidden {#1}}


%% VII.2 - Custom tables for piscine


\newcommand{\makeheader}
{
  \begin{tabularx}{\textwidth}{|X X  X X|}
    \hline
  \multicolumn{1}{|>{\raggedright}m{1cm}|}
              {\includegraphics[height=1cm]{koala.png}} & 
  \multicolumn{2}{>{\centering}m{12cm}}{\small Exercice : \@exnumber } &
  \multicolumn{1}{ >{\raggedleft}p{1.5cm}|} 
              {\scriptsize points : \@exscore} \\ \hline

  \multicolumn{4}{|>{\centering}m{15cm}|}
              {\small \@extitle} \\ \hline

  \multicolumn{4}{|>{\raggedright}m{15cm}|}
              {\small R\'{e}pertoire de rendu: \ttfamily 
                \@turnindir\@daypiscine/ex\@exnumber }
              \\ \hline

  \multicolumn{2}{|>{\raggedright}m{7.5cm}}
              {\small Compilateur : \ttfamily \@excompil } & 
  \multicolumn{2}{|>{\raggedright}m{7.5cm}|}
              {\small Flags de compilation: 
                \ttfamily \@exflags }
              \\ \hline

  \multicolumn{2}{|>{\raggedright}m{7.52cm}}
              {\small Makefile : \ttfamily{\@exmake}} &  
  \multicolumn{2}{|>{\raggedright}m{7.5cm}|}
              {R\`{e}gles : \ttfamily \@exrules } \\ \hline

  \multicolumn{4}{|>{\raggedright}m{15cm}|}
              {\small Fichiers a rendre : \ttfamily \@exfiles }
              \\ \hline
                    
   \multicolumn{4}{|>{\raggedright}m{15cm}|}
               {\small Remarques : \ttfamily \@exnotes } 
               \\ \hline

   \multicolumn{4}{|>{\raggedright}m{15cm}|}
               {\small Fonctions Interdites : \ttfamily \@exforbidden } 
               \\ \hline
\end{tabularx}
\exnotes
\exrules
\exmake
\exforbidden
\extitle{}
\exnumber{}
}
