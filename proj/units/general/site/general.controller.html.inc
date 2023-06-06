<?php

	namespace Proj\Site\Units\HTML;

	require DIR_UNITS . 'general/site/general.actions.inc';
//require DIR_UNITS . 'general/general.consts.inc';
//require DIR_UNITS . 'general/site/views/About.tpl';
//require DIR_UNITS . 'general/site/views/Contacts.tpl';
//require DIR_UNITS . 'general/site/views/PrivacyPolicy.tpl';
//require DIR_UNITS . 'general/site/views/TermsUse.tpl';
//require DIR_UNITS . 'general/site/views/Header.tpl';
//require DIR_UNITS . 'general/site/views/Footer.tpl';
//require DIR_UNITS . 'general/site/views/Donations.tpl';
//
//use JetBrains\PhpStorm\NoReturn;
//
//use Base\Units;
//use Base\Instance;
//use Base\Action;
//use Proj\Units\Consts;
//use Proj\Site\Params;
//use Proj\Site\Templates\Template;
//use Proj\Site\Templates\Layout;
//use Proj\Site\Templates\General\About;
//use Proj\Site\Templates\General\Contacts;
//use Proj\Site\Templates\General\PrivacyPolicy;
//use Proj\Site\Templates\General\TermsUse;
//use Proj\Site\Templates\General\Header;
//use Proj\Site\Templates\General\Footer;
//use Proj\Site\Templates\General\Donations;
//
//class General extends Units implements Consts\General {
//	use Instance;
//
//	public Action $set_data_page;
//
//	public Action $home;
//	public Action $about;
//	public Action $contacts;
//	public Action $privacy_policy;
//	public Action $terms_use;
//
//	public Action $header;
//	public Action $footer;
//
//	public Action $donations;
//
//	private function __construct() {
//		parent::__construct(self::ID, self::NAME);
//
//		$this->set_data_page			= new Action('always', 'always');
//
//		$this->home						= new Action('null', 'null', 'default');
//		$this->about					= new Action('about', 'null', 'default');
//		$this->contacts					= new Action('contacts', 'null', 'default');
//		$this->privacy_policy			= new Action('documents', 'privacy_policy', 'default');
//		$this->terms_use				= new Action('documents', 'terms_use', 'default');
//
//		$this->header					= new Action('always', 'always');
//		$this->footer					= new Action('always', 'always');
//
//		$this->donations				= new Action('donations', 'null', 'default', /* @lang JavaScript */ "Site.General.On(); return false;");
//
//		self::$view->Push($this->set_data_page, [$this, 'SetDataPage']);
//
//		self::$view->Push($this->home, [$this, 'Home']);
//		self::$view->Push($this->about, [$this, 'About']);
//		self::$view->Push($this->contacts, [$this, 'Contacts']);
//		self::$view->Push($this->privacy_policy, [$this, 'OutPrivacyPolicy']);
//		self::$view->Push($this->terms_use, [$this, 'OutTermsUse']);
//
//		self::$view->Push($this->header, [$this, 'OutHeader']);
//		self::$view->Push($this->header, [$this, 'OutFooter']);
//
//		self::$view->Push($this->donations, [$this, 'OnDonations']);
//	}
//
//	public function SetDataPage() {
//		$path = [];
//		if (self::$area != 'null') $path[] = self::$area;
//		if (self::$part != 'null') $path[] = self::$part;
//		$value = $path ? implode('_', $path) : 'main';
//		Template::instance()->SetDataPage($value);
//	}
//
//	public function Home() {
//		Template::instance()->SetTitle(Params::$site_name . ' | Главная');
//		Template::instance()->SetDescription(Params::$site_name . ' - ресурс в помощь ИП, самозанятым с документами и отчётами');
//		Template::instance()->SetKeywords('прайс-лист онлайн, составить акт выполненных работ, смета бесплатно, документы для ИП, отчёты самозанятые');
//	}
//
//	public function About() {
//		Template::instance()->SetTitle(Params::$site_name . ' | О проекте');
//		Template::instance()->SetDescription('О проекте ' . Params::$site_name);
//		Template::instance()->SetKeywords('проект ' . Params::$site_name);
//		Layout::instance()->main->Push(About::ToVar());
//	}
//
//	public function Contacts() {
//		Template::instance()->SetTitle(Params::$site_name . ' | Контакты');
//		Template::instance()->SetDescription('Контакты');
//		Template::instance()->SetKeywords('контакты');
//		Layout::instance()->main->Push(Contacts::ToVar());
//	}
//
//	public function OutPrivacyPolicy() {
//		Template::instance()->SetTitle(Params::$site_name . ' | Политика конфиденциальности');
//		Template::instance()->SetDescription('Политика конфиденциальности ' . Params::$site_name);
//		Template::instance()->SetKeywords('политика конфиденциальности');
//		Layout::instance()->main->Push(PrivacyPolicy::ToVar());
//	}
//
//	public function OutTermsUse() {
//		Template::instance()->SetTitle(Params::$site_name . ' | Пользовательское соглашение');
//		Template::instance()->SetDescription('Пользовательское соглашение ' . Params::$site_name);
//		Template::instance()->SetKeywords('пользовательское соглашение');
//		Layout::instance()->main->Push(TermsUse::ToVar());
//	}
//
//	public function OutHeader() {
//		Layout::instance()->header->Push(Header::ToVar());
//	}
//
//	public function OutFooter() {
//		Layout::instance()->footer->Push(Footer::ToVar());
//	}
//
//	#[NoReturn] public function OnDonations() {
//		SendJSONSuccess(['html' => Donations::ToVar()]);
//	}
//
//}
//
//General::init();