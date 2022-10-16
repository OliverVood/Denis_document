<?php

	namespace PROJ\Units;

	use Base\Units;
	use Base\Instance;
	use Proj\Units\Consts;

	require DIR_UNITS . 'catalogs/consts.inc';

	class Catalogs extends Units implements Consts\Catalogs {
		use Instance;

		public function __construct() {
			parent::__construct(self::ID, self::NAME);
		}

		public function test() {
			echo '4321 ';
		}

		public function test1() {
			echo 'dfdf ';
		}

	}

	Catalogs::init();