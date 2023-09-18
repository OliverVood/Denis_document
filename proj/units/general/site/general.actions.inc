<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'general/general.consts.inc';

	use Base\Units;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class General extends Units implements Consts\General {
		public static Action $set_data_page;

		public static Action $home;
		public static Action $about;
		public static Action $contacts;
		public static Action $privacy_policy;
		public static Action $terms_use;
		public static Action $error404;

		public static Action $header;
		public static Action $footer;

		public static Action $donations;

		protected function __construct($file) {
			parent::__construct($file);
		}

		public static function RegActions() {
			self::$set_data_page		= new Action('always', 'always');

			self::$home					= new Action('null', 'null', 'default');
			self::$about				= new Action('about', 'null', 'default');
			self::$contacts				= new Action('contacts', 'null', 'default');
			self::$privacy_policy		= new Action('documents', 'privacy_policy', 'default');
			self::$terms_use			= new Action('documents', 'terms_use', 'default');
			self::$error404				= new Action('404', 'null', 'default');

			self::$header				= new Action('always', 'always');
			self::$footer				= new Action('always', 'always');

			self::$donations			= new Action('donations', 'null', 'default', /* @lang JavaScript */ "Base.Common.Query.Send('/donations', Site.General.OnDonations); return false;");
		}

	}

	General::RegActions();