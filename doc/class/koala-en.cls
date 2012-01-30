%******************************************************************************%
%                                                                              %
%                           koala.cls                                          %
%                           Made by:                                           %
%                                Maxime MONTINET                               %
%                                David GIRON                                   %
%                                Uriel `korfuri' CORFA <korfuri@korfuri.fr>    %
%                                                                              %
%******************************************************************************%


\NeedsTeXFormat{LaTeX2e}[1995/12/01]
\ProvidesClass{koala-en}[2010/07/15 v2.0
  LaTeX class for Koala-themed documents - English language]

\LoadClass[]{koala}

\DeclareOption*{%
  % Pass every unknown option to the article class
  \PassOptionsToClass{\CurrentOption}{koala}
}
\ProcessOptions\relax
