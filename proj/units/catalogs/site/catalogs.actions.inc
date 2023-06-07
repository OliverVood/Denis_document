<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'catalogs/catalogs.consts.inc';

	use Base\Units;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class Catalogs extends Units implements Consts\Catalogs {
		public static Action $out_buttons;
		public static Action $action_estimate;
		public static Action $action_certificate;
		public static Action $action_price_list;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
		}

		public static function RegActions() {
			self::$out_buttons			= new Action('null', 'null');
			self::$action_estimate		= new Action('estimate', 'null', '/estimate');
			self::$action_certificate	= new Action('certificate', 'null', '/certificate');
			self::$action_price_list	= new Action('price_list', 'null', '/price_list');
		}

	}

	Catalogs::RegActions();