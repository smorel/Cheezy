/*
	Transition header file.
*/

#ifndef _QFORMAT_FACTORY_H_


class QFormatFactory : public QFormatScheme
{
	public:
		inline QFormatFactory(QObject *p = 0) : QFormatScheme(p) {}
		inline QFormatFactory(const QString& f, QObject *p = 0) : QFormatScheme(f, p) {}
};

#endif
