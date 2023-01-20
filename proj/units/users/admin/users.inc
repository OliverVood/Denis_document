<?php

	namespace Proj\Admin\Units;

	require 'users.structure.inc';

	use Base\Instance;
	use Proj\Site\Structure;

	class Users extends Structure\Users {
		use Instance;

		private string | null $uid = null;

		private function __construct() {
			parent::__construct();
		}

	}

	Users::init();