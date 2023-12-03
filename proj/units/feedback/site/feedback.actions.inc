<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'feedback/feedback.consts.inc';

	use Base\Units;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class Feedback extends Units implements Consts\Feedback {
		public static Action $feedback;
		public static Action $do_feedback;

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, $file);
		}

		public static function RegActions() {
			self::$feedback				= new Action(self::NAME, 'null', 'default', /* @lang JavaScript */ "Base.Common.Query.Send('/feedback', Site.Feedback.On); return false;");
			self::$do_feedback			= new Action(self::NAME, 'do', 'default', /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this, Site.Feedback.Do); return false;");
		}

	}

	Feedback::RegActions();