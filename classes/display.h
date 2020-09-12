#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/**
 * classe responsável por obter informações do monitor
 */
class Display
{
public:
	/** obtém a largura em pixels da área do monitor */
	static int getWidth();
	/** obtém a altura em pixels da área do monitor */
	static int getHeight();
};

#endif
