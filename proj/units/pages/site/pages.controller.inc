<?php

	namespace Proj\Site\Units;

    require DIR_UNITS . 'pages/site/pages.actions.inc';

	require DIR_UNITS . 'pages/site/views/About.tpl';
	require DIR_UNITS . 'pages/site/views/Contacts.tpl';
	require DIR_UNITS . 'pages/site/views/PrivacyPolicy.tpl';
	require DIR_UNITS . 'pages/site/views/TermsUse.tpl';

	require DIR_UNITS . 'pages/site/views/Header.tpl';
	require DIR_UNITS . 'pages/site/views/Footer.tpl';

	require DIR_UNITS . 'pages/site/views/Donations.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Base\Helper\Response;
	use Proj\Params;
	use Proj\Site\Actions;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Template;
	use Proj\Site\Templates as TPLs;
	use Closure;

	class Pages extends Actions\Pages {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);

			self::$view->Push([self::ENTRY_HTML], self::$set_data_page, Closure::fromCallable([$this, 'SetDataPage']));

			self::$view->Push([self::ENTRY_HTML], self::$home, Closure::fromCallable([$this, 'Home']));
			self::$view->Push([self::ENTRY_HTML], self::$about, Closure::fromCallable([$this, 'About']));
			self::$view->Push([self::ENTRY_HTML], self::$contacts, Closure::fromCallable([$this, 'Contacts']));
			self::$view->Push([self::ENTRY_HTML], self::$privacy_policy, Closure::fromCallable([$this, 'OutPrivacyPolicy']));
			self::$view->Push([self::ENTRY_HTML], self::$terms_use, Closure::fromCallable([$this, 'OutTermsUse']));
			self::$view->Push([self::ENTRY_HTML], self::$estimate, Closure::fromCallable([$this, 'OutEstimate']));
			self::$view->Push([self::ENTRY_HTML], self::$certificate, Closure::fromCallable([$this, 'OutCertificate']));
			self::$view->Push([self::ENTRY_HTML], self::$price_list, Closure::fromCallable([$this, 'OutPriceList']));
			self::$view->Push([self::ENTRY_HTML], self::$news_all, Closure::fromCallable([News::instance(), 'OnViewAll']));
			self::$view->Push([self::ENTRY_HTML], self::$news_show, Closure::fromCallable([News::instance(), 'OnViewShow']));
			self::$view->Push([self::ENTRY_HTML], self::$changes_list, Closure::fromCallable([Changes::instance(), 'OnViewList']));
			self::$view->Push([self::ENTRY_HTML], self::$changes_show, Closure::fromCallable([Changes::instance(), 'OnViewShow']));
			self::$view->Push([self::ENTRY_HTML], self::$error404, Closure::fromCallable([$this, 'Error404']));

			self::$view->Push([self::ENTRY_HTML], self::$header, Closure::fromCallable([$this, 'OutHeader']));
			self::$view->Push([self::ENTRY_HTML], self::$footer, Closure::fromCallable([$this, 'OutFooter']));

			self::$view->Push([self::ENTRY_XHR], self::$donations, Closure::fromCallable([$this, 'OnDonations']));
		}

		#region HTML
		private function SetDataPage() {
			$path = [];
			if (self::$area != 'null') $path[] = self::$area;
			if (self::$part != 'null') $path[] = self::$part;
			$value = $path ? implode('_', $path) : 'main';
			Template::instance()->SetDataPage($value);
		}

		private function Home() {
			Template::instance()->SetTitle(Params::$site_name . ' | Главная');
			Template::instance()->SetDescription(Params::$site_name . ' - ресурс в помощь ИП, самозанятым с документами и отчётами');
			Template::instance()->SetKeywords('прайс-лист онлайн, составить акт выполненных работ, смета бесплатно, документы для ИП, отчёты самозанятые');
			Layout::instance()->main->Push(TPLs\Catalogs\Buttons::ToVar());
			Layout::instance()->main->Push(News::instance()->GetViewLast(3));
			Layout::instance()->main->Push(Changes::instance()->GetViewLast(4));
		}

		private function About() {
			Template::instance()->SetTitle(Params::$site_name . ' | О проекте');
			Template::instance()->SetDescription('О проекте ' . Params::$site_name);
			Template::instance()->SetKeywords('проект ' . Params::$site_name);
			Layout::instance()->main->Push(TPLs\Pages\About::ToVar());
		}

		private function Contacts() {
			Template::instance()->SetTitle(Params::$site_name . ' | Контакты');
			Template::instance()->SetDescription('Контакты');
			Template::instance()->SetKeywords('контакты');
			Layout::instance()->main->Push(TPLs\Pages\Contacts::ToVar());
		}

		private function OutPrivacyPolicy() {
			Template::instance()->SetTitle(Params::$site_name . ' | Политика конфиденциальности');
			Template::instance()->SetDescription('Политика конфиденциальности ' . Params::$site_name);
			Template::instance()->SetKeywords('политика конфиденциальности');
			Layout::instance()->main->Push(TPLs\Pages\PrivacyPolicy::ToVar());
		}

		private function OutTermsUse() {
			Template::instance()->SetTitle(Params::$site_name . ' | Пользовательское соглашение');
			Template::instance()->SetDescription('Пользовательское соглашение ' . Params::$site_name);
			Template::instance()->SetKeywords('пользовательское соглашение');
			Layout::instance()->main->Push(TPLs\Pages\TermsUse::ToVar());
		}

		private function OutEstimate(): void {
			Template::instance()->SetTitle(Params::$site_name . ' | Сметы');
			Template::instance()->SetDescription('Составление сметы на оказание услуг и продажу товаров');
			Template::instance()->SetKeywords('смета онлайн бесплатно, документы для самозанятых');
			Layout::instance()->main->Push(TPLs\Catalogs\Estimate::ToVar());
		}

		private function OutCertificate(): void {
			Template::instance()->SetTitle(Params::$site_name . ' | Акты выполненных работ');
			Template::instance()->SetDescription('акт выполненных работ, для ИП, отчёты');
			Template::instance()->SetKeywords('');
			Layout::instance()->main->Push(TPLs\Catalogs\Certificate::ToVar());
		}

		private function OutPriceList(): void {
			Template::instance()->SetTitle(Params::$site_name . ' | Прайс-листы');
			Template::instance()->SetDescription('Составление прайс-листа на оказание услуг, проведение работ и продажу товаров');
			Template::instance()->SetKeywords('прайс-лист онлайн, отчет оказание услуг, перечень цен на товары');
			Layout::instance()->main->Push(TPLs\Catalogs\PriceList::ToVar());
		}

		private function Error404() {
			Layout::instance()->main->Push('<h1>Страница не найдена!<h1>');
		}

		private function OutHeader() {
			Layout::instance()->header->Push(TPLs\Pages\Header::ToVar());
		}

		private function OutFooter() {
			Layout::instance()->footer->Push(TPLs\Pages\Footer::ToVar());
		}

		#endregion HTML

		#region XHR

		#[NoReturn] private function OnDonations() {
			Response::PushData(['html' => TPLs\Pages\Donations::ToVar()]);
			Response::SendJSON();
		}

		#endregion XHR

	}

	Pages::init();