<?php

	namespace Proj\Site\Model;

	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\DBQuery;

	class Feedback {
		use Instance;

		private DBQuery $db;

		private function __construct() {
			$this->db = DBQuery::instance();
		}

		public function InsertFeedback($state, $name, $contacts, $letter, $content): void {
			$this->db->Insert(Consts\Feedback::TABLES['feedback'], [
				'state' => $state,
				'name' => $name,
				'contacts' => $contacts,
				'letter' => $letter,
				'content' => $content,
			]);
		}

	}

	Feedback::init();