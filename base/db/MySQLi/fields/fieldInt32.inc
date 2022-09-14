<?php

	namespace Base\DB;

	use Base\DB;

	class FieldInt32 extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('int32', $name);
		}

	}