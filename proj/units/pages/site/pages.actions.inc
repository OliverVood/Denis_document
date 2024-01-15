<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'pages/pages.consts.inc';

	use Base\Unit;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class Pages extends Unit implements Consts\Pages {
		public static Action $set_data_page;

		public static Action $header;
		public static Action $footer;

		public static Action $home;
		public static Action $about;
		public static Action $contacts;
		public static Action $privacy_policy;
		public static Action $terms_use;
		public static Action $estimate;
		public static Action $certificate;
		public static Action $price_list;
		public static Action $news_all;
		public static Action $news_show;
		public static Action $changes_list;
		public static Action $changes_show;
		public static Action $error404;

		public static Action $donations;

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {
			self::$set_data_page		= new Action('always', 'always');

			self::$header				= new Action('always', 'always');
			self::$footer				= new Action('always', 'always');

			self::$home					= new Action('null', 'null', 'default');
			self::$about				= new Action('about', 'null', 'default');
			self::$contacts				= new Action('contacts', 'null', 'default');
			self::$privacy_policy		= new Action('documents', 'privacy_policy', 'default');
			self::$terms_use			= new Action('documents', 'terms_use', 'default');
			self::$estimate				= new Action('estimate', 'null', '/estimate');
			self::$certificate			= new Action('certificate', 'null', '/certificate');
			self::$price_list			= new Action('price_list', 'null', '/price_list');
			self::$news_all				= new Action('news', 'null', 'default');
			self::$news_show			= new Action('news', 'show', "/news/show?id=%id%");
			self::$changes_list			= new Action('changes', 'null', 'default');
			self::$changes_show			= new Action('changes', 'show', "/changes/show?id=%id%");
			self::$error404				= new Action('404', 'null', 'default');

			self::$donations			= new Action('donations', 'null', 'default', /* @lang JavaScript */ "Base.Common.Query.Send('/donations', Site.General.OnDonations); return false;");
		}

	}

	Pages::RegActions();