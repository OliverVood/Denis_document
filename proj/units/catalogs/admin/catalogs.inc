<?php

	namespace Proj\Admin\Units;

	use Base\Units;
	use Base\Instance;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;
	use Proj\DBObject;

	require DIR_UNITS . 'catalogs/consts.inc';

	class Catalogs extends Units implements Consts\Catalogs {
		use Instance;

		private DBObject $db;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();
		}

	}

	Catalogs::init();