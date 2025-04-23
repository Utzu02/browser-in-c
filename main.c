/* TUDORESCU IOAN DANIEL - 312CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// struct page
typedef struct
{
	int ID;
	char URL[100];
	char *desc;
} page, *tpage;

/// struct stack (preluat din modelul de curs)
typedef struct cell
{
	tpage elem;
	struct cell *next;
} stack, *tstack;

/// struct tab (lista dublu inlantuita circulara cu santinela)
typedef struct tab
{
	struct tab *next;
	struct tab *prev;
	int ID;
	page *page_adr;
	tstack forward, backward;
} tab, *ttab;

/// struct browser
typedef struct
{
	tab *current_tab;
	ttab tabs;
} browser_template;

/// functie print eroare
void print_error(FILE *out)
{
	fprintf(out, "%s\n", "403 Forbidden");
}

/// functie initializare stiva
tstack init_stack(void)
{
	tstack s;
	s = NULL;
	return s;
}

/// functie verificare daca stiva este goala
int is_empty_stack(tstack s)
{
	if (!s)
		return 1;
	return 0;
}

/// functie adaugare element nou in stiva
tstack push(tstack s, tpage el)
{
	tstack t;
	t = (tstack)malloc(sizeof(stack));
	if (!t)
		return NULL;
	t->elem = el;
	t->next = s;
	return t;
}

/// functie stergere element din stiva
tstack pop(tstack s)
{
	tstack t;
	if (!s)
		return NULL;
	t = s;
	s = s->next;
	free(t);
	return s;
}

/// functie adaugare tab nou (adaptat dupa modelul de curs)
void add_tab(ttab nou, ttab pos)
{
	nou->next = pos->next;
	nou->prev = pos;
	pos->next = nou;
	nou->next->prev = nou;
}

/// functie eliminare tab (model de curs)
void del_tab(ttab pos)
{
	/// golim stiva de backward
	while (pos->backward)
		pos->backward = pop(pos->backward);
	/// golim stiva de forward
	while (pos->forward)
		pos->forward = pop(pos->forward);
	ttab prec, urm;
	prec = pos->prev; // predecesorul nodului de sters
	urm = pos->next;  // urmatorul element
	prec->next = urm;
	urm->prev = prec;
	free(pos);
}

/// functie initializare tab (si variabile din el exemplu stive)
ttab init_tab(void)
{
	ttab s;
	s = (ttab)malloc(sizeof(tab));
	s->next = s;
	s->prev = s;
	s->backward = init_stack();
	s->forward = init_stack();
	s->ID = -1;
	s->page_adr = NULL;
	return s;
}

/// functie cautare tab cu ID-ul x
ttab pos(ttab s, int x)
{
	ttab p = s->next;
	// primul element cu date
	while (p != s && x != p->ID)
		// cauta pe x in lista
		p = p->next;
	if (p == s)
		return s; // negasit
	else
		return p; // gasit la adresa p
}

/// functie afisare ID-uri tab incepand de la cel curent in dreapta
void print_tab(ttab p, ttab s, FILE *out)
{
	ttab current = p;
	/// cazul in care este un singur tab deschis
	if (p->next->next == current) {
		fprintf(out, "%d\n", p->ID);
	} else {
		/// parcurgem pana la tab ul curent
		while (p->next != current)
		{
			/// verificam sa nu accesam santinela
			if (p != s)
				fprintf(out, "%d ", p->ID);
			p = p->next;
		}
		/// in cazul in care tab ul curent incepe de la ID-ul 0
		if (current == s->next)
			fprintf(out, "\n");
		else
			fprintf(out, "%d\n", p->ID);
	}
}

/// functie adaugare tab nou (adaptat dupa modelul de curs, initializam stivele)
ttab new_tab(ttab tabs, tpage pages, int tab_ids)
{
	ttab nou;
	nou = (ttab)malloc(sizeof(tab));
	nou->page_adr = pages + 0;
	nou->ID = tab_ids;
	nou->backward = init_stack();
	nou->forward = init_stack();
	add_tab(nou, tabs->prev);
	return nou;
}

/// functie cautare pagina dupa un ID specific
int search_page(page *pages, int key, int nr_pag)
{
	for (int i = 0; i <= nr_pag; ++i)
		if (pages[i].ID == key)
			return i;
	return -1;
}

/// functie inchidere tab
void close_tab(browser_template *browser)
{
	ttab current = browser->current_tab;
	browser->current_tab = browser->current_tab->prev;
	if (browser->current_tab == browser->tabs)
		browser->current_tab = browser->tabs->prev;
	del_tab(current);
}

/// functie initializare browser
browser_template init_browser(page *pages)
{
	browser_template browser;
	ttab s = NULL, p = NULL, nou = NULL;
	s = init_tab();
	p = s;
	/// adaugam tab ul cu ID-ul 0
	nou = (ttab)malloc(sizeof(tab));
	nou->page_adr = pages;
	nou->ID = 0;
	/// initializam stivele din tab ul din ID ul 0
	nou->forward = init_stack();
	nou->backward = init_stack();
	add_tab(nou, p);
	p = nou;
	browser.tabs = s;
	browser.current_tab = p;
	return browser;
}

/// functie print history
void print_history(ttab tab_found, FILE *out)
{
	/// afisam pagina curenta din tab
	fprintf(out, "%s\n", tab_found->page_adr->URL);
	/// parcurgem stiva forward
	tstack nou = tab_found->forward;
	if (!is_empty_stack(nou))
	{
		while (nou)
		{
			fprintf(out, "%s\n", nou->elem->URL);
			nou = nou->next;
		}
	}
	/// parcurgem stiva backward
	nou = tab_found->backward;
	if (!is_empty_stack(nou))
	{
		while (nou)
		{
			fprintf(out, "%s\n", nou->elem->URL);
			nou = nou->next;
		}
	}
}

/// functie backward
void backward(ttab current_tab)
{
	tpage current_page = current_tab->page_adr;
	/// adaugam in stiva forward tab ul curent
	current_tab->forward = push(current_tab->forward, current_page);
	tpage new_page = current_tab->backward->elem;
	/// stergem din stiva backward tab ul curent
	current_tab->backward = pop(current_tab->backward);
	current_tab->page_adr = new_page;
}

/// functie forward
void forward(ttab current_tab)
{
	tpage current_page = current_tab->page_adr;
	/// adaugam in stiva backward tab ul curent
	current_tab->backward = push(current_tab->backward, current_page);
	tpage new_page = current_tab->forward->elem;
	/// stergem din stive forward tab ul curent
	current_tab->forward = pop(current_tab->forward);
	current_tab->page_adr = new_page;
}

/// functie open page
void open_page(ttab current_tab, tpage pages)
{
	/// verificam daca stiva forward este goala, daca nu este o golim
	while (!is_empty_stack(current_tab->forward))
		current_tab->forward = pop(current_tab->forward);
	tpage current_page = current_tab->page_adr;
	current_tab->backward = push(current_tab->backward, current_page);
	current_tab->page_adr = pages;
}

/// functie init pages (pentru prima pagina)
tpage init_pages(void)
{
	tpage pages = (tpage)malloc(1 * sizeof(page));
	pages[0].ID = 0;
	strcpy(pages[0].URL, "https://acs.pub.ro/");
	pages[0].desc = (char *)malloc(17 * sizeof(char));
	strcpy(pages[0].desc, "Computer Science");
	return pages;
}

/// functie read pages (returneaza vectorul pages)
tpage read_pages(FILE *in, int nr_pag)
{
	tpage pages = init_pages();
	int i = 0;
	char description[512];
	for (i = 1; i <= nr_pag; ++i)
	{
		/// realocam vectorul dinamic
		pages = (tpage)realloc(pages, (i + 1) * sizeof(page));
		fscanf(in, "%d %s", &pages[i].ID, pages[i].URL);
		fgetc(in);
		fgets(description, 512, in);
		description[strcspn(description, "\n")] = 0;
		pages[i].desc = malloc((strlen(description) + 1) * sizeof(char));
		strcpy(pages[i].desc, description);
	}
	return pages;
}

/// functie free pentru leak uri de memorie
void free_all(browser_template *browser, page *pages, int nr_pag)
{
	for (int i = 0; i <= nr_pag; ++i)
		free(pages[i].desc);
	ttab p = browser->tabs->next;
	while (p != browser->tabs)
	{
		ttab next = p->next;
		while (!is_empty_stack(p->backward))
			p->backward = pop(p->backward);

		while (!is_empty_stack(p->forward))
			p->forward = pop(p->forward);
		free(p);
		p = next;
	}
	free(browser->tabs);
	free(pages);
}

int main(void)
{
	/// deschidem fisierele in/out
	FILE *in = fopen("tema1.in", "r");
	FILE *out = fopen("tema1.out", "w");
	int nr_pag = 0, i = 0, nr_op = 0, tab_ids = 0, id_op = 0;
	char operatie[64];
	fscanf(in, "%d", &nr_pag);
	/// citim paginile
	tpage pages = read_pages(in, nr_pag);
	/// initializam browserul cu prima pagina
	browser_template browser = init_browser(pages);
	/// citim numarul de operatii
	fscanf(in, "%d", &nr_op);
	fgetc(in);
	for (i = 0; i < nr_op; ++i)
	{
		fscanf(in, "%s", operatie);
		/// stergem newline ul din string ul operatie
		operatie[strcspn(operatie, "\n")] = 0;
		if (strcmp(operatie, "PRINT") == 0)
		{
			/// afisaram tab urile
			print_tab(browser.current_tab, browser.tabs, out);
			/// afisam descrierea de la pagina tab ului curent
			fprintf(out, "%s\n", browser.current_tab->page_adr->desc);
		} else if (strcmp(operatie, "NEW_TAB") == 0) {
			/// incrementam variabil tab_ids
			browser.current_tab = new_tab(browser.tabs, pages, ++tab_ids);
		} else if (strcmp(operatie, "CLOSE") == 0) {
			/// daca tab ul curent este cel cu ID 0 afisam eroare
			if (browser.current_tab->prev == browser.tabs)
				print_error(out);
			else
				close_tab(&browser);
		} else if (strcmp(operatie, "OPEN") == 0) {
			fscanf(in, "%d", &id_op);
			fgetc(in);
			/// cautam tab ul cu ID-ul id_op
			ttab tab_found = pos(browser.tabs, id_op);
			/// daca tab_found este santinela afisam eroare
			if (tab_found == browser.tabs)
				print_error(out);
			else
				browser.current_tab = tab_found;
		} else if (strcmp(operatie, "NEXT") == 0) {
			/// trecem la tab ul urmator
			browser.current_tab = browser.current_tab->next;
			/// verificam daca este santinela
			if (browser.current_tab == browser.tabs)
				browser.current_tab = browser.tabs->next;
		} else if (strcmp(operatie, "PREV") == 0) {
			/// trecem la tab ul anterior
			browser.current_tab = browser.current_tab->prev;
			/// verificam daca este santinela
			if (browser.current_tab == browser.tabs)
				browser.current_tab = browser.tabs->prev;
		} else if (strcmp(operatie, "PAGE") == 0) {
			fscanf(in, "%d", &id_op);
			fgetc(in);
			/// cautam pagina cu ID ul id_op
			int search = search_page(pages, id_op, nr_pag);
			/// daca nu o gasim afisam eroare
			if (search == -1)
				print_error(out);
			else
				open_page(browser.current_tab, pages + search);
		} else if (strcmp(operatie, "BACKWARD") == 0) {
			/// verificam daca stiva backward este goala
			if (is_empty_stack(browser.current_tab->backward))
				print_error(out);
			else
				backward(browser.current_tab);
		} else if (strcmp(operatie, "FORWARD") == 0) {
			/// verificam daca stiva forward este goala
			if (is_empty_stack(browser.current_tab->forward))
				print_error(out);
			else
				forward(browser.current_tab);
		} else if (strcmp(operatie, "PRINT_HISTORY") == 0) {
			fscanf(in, "%d", &id_op);
			fgetc(in);
			/// cautam tab ul cu ID ul id_op
			ttab tab_found = pos(browser.tabs, id_op);
			/// daca este santinela afisam eroare
			if (tab_found == browser.tabs)
				print_error(out);
			else
				print_history(tab_found, out);
		}
	}
	/// dam free la structurile declarate
	free_all(&browser, pages, nr_pag);
	/// inchidem fisierele de in/out
	fclose(in);
	fclose(out);
	return 0;
}
