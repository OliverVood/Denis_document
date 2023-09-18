<?php

	namespace Proj\Admin\Model;

	use Base\Model;
	use Base\Instance;
	use Proj\DBObject;

	class General extends Model {
		use Instance;

		private DBObject $db;

		private function __construct() {
			parent::__construct(__FILE__);
			$this->db = DBObject::instance();
		}

		public function Home(): string {
			return 'Главная';
		}

		public function Structure(): array {
			return $this->db->Structure();
		}

		public function DBCheck(): array {
			return $this->db->Check();
		}

		public function DBMake(): array {
			$this->db->Make();
			return $this->db->Check();
		}

	}

	General::init();