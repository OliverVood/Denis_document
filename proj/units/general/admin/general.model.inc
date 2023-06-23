<?php

	namespace Proj\Admin\Model;

	use Base\Instance;
	use Proj\DBObject;

	class General {
		use Instance;

		private DBObject $db;

		private function __construct() {
			$this->db = DBObject::instance();
		}

		public function Home(): string {
			return 'Главная';
		}

		public function Structure(): array {
			return [];
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