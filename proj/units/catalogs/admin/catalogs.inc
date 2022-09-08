<?php

	namespace PROJ\Units;

	use Base\Units\Units;
	use Base\Units\Objects;

	require DIR_UNITS . 'catalogs/consts.inc';

	class Catalogs extends Units implements Consts\Catalogs {
		use Objects;

		public function __construct() {
			parent::__construct(self::ID, self::NAME);
			self::$object = $this;
		}

		public function test() {
			echo '4321 ';
		}

		public function test1() {
			echo 'dfdf ';
		}

	}

	Catalogs::init();